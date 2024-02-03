#include "Game.hpp"
#include "Deck.hpp"
#include "Dealer.hpp"
#include "Player.hpp"
#include "Actions.hpp"
#include "Status.hpp"
#include "BlackJack.hpp"

#include <string>
#include <iostream>

void Game::setPlayerStatus(Status &player, Status statusType) {
	player = statusType;
}

void Game::setGameStatus(Game& _game, GameStatus statusType) {
	_game.__gameStatus = statusType;
}

bool Game::setSession(bool &_session, bool type) {
	_session = type;
	return type;
}

Game::Game(std::string name, Balance& _balance) {
	if (!name.empty()) {
		__deck = Deck();
		int stake = __checkStake(_balance);
		__dealer = Dealer(__deck);
		__player = Player(__deck, name, _balance, stake);
	}
}

int Game::__checkStake(Balance& _balance) {
	int stake;
	std::cout << "\nEnter your stake: ";
	try { std::cin >> stake; }
	catch (const std::exception&) {
		std::cerr << "\nWrong type of data! Try again!";
		return __checkStake(_balance);
	}
	if (stake <= 0) {
		std::cerr << "\nStake must be above 0! Try again!";
		return __checkStake(_balance);
	}
	if (stake > getBalance(_balance)) {
		std::cerr << "\nYou dont have enough money to make a stake! Try again!";
		return __checkStake(_balance);
	}
	return stake;
}

void Game::updateHandCount(Card card, int& counter) {
	counter += card.value;
}

void Game::updateHandCount(int aceValue, int& counter) {
	if (aceValue == 1) {
		counter -= 10;
	}
}

bool Game::__checkForAce(Game& _game) {
	if (!_game.__balanceNeed) {
		for (auto x : _game.__dealer.getDealerHand(true)) {
			if (x.shortName == "A") {
				_game.__balanceNeed = true;
				return _game.__balanceNeed;
			}
		}
		for (auto x : _game.__player.getPlayerHand(true)) {
			if (x.shortName == "A") {
				_game.__balanceNeed = true;
				return _game.__balanceNeed;
			}
		}
		return _game.__balanceNeed;
	}
}

void Game::__swapAceValues(Game& _game, int player) {
	if (player == 0) {
		for (auto &card : _game.__dealer.getDealerHand(true)) {
			if (card.shortName == "A") {
				int dealerCount = _game.__dealer.getDealerCount();
				if (dealerCount > 21 && card.value == 11) {
					card.value = 1;
					_game.__dealer.updateDealerCount(card.value);
				}
			}
		}
	}
	else {
		for (auto &card : _game.__player.getPlayerHand(true)) {
			if (card.shortName == "A") {
				int playerCount = _game.__player.getPlayerCount();
				if (playerCount > 21 && card.value == 11) {
					card.value = 1;
					_game.__player.updatePlayerCount(card.value);
				}
			}
		}
	}
}

void Game::__balanceAce(Game& _game, bool& balanceNeed) {
	if (balanceNeed) {
		int dealerCount = _game.__dealer.getDealerCount();
		if (dealerCount > 21) {
			_game.__swapAceValues(_game, 0);
		}

		int playerCount = _game.__player.getPlayerCount();
		if (playerCount > 21) {
			_game.__swapAceValues(_game, 1);
		}
	}
}

void Game::prepareGame(Game &_game, bool &_session, Balance& _balance, std::string& name) {
	using namespace std;
	cout << "Hi " << name << ", now we are gonna start the first game!\n";
	cout << "Your initial balance is: " << getBalance(_balance) << std::endl;
	_game = createGame(name, _balance);

	__checkForAce(_game);
	__balanceAce(_game, _game.__balanceNeed);
	_game.__currentSession = setSession(_session, true);
	setPlayerStatus(_game.__dealer.dealerStatus, Status::PROGRESS);
	setPlayerStatus(_game.__player.playerStatus, Status::PROGRESS);
	setGameStatus(_game, GameStatus::PROGRESS);
	startGame(_game, _session, _balance);
}

Game Game::createGame(std::string& name, Balance& _balance) {
	Game game(name, _balance);
	return game;
}


GameStatus Game::checkPlayersScores(Game& _game, Balance& _balance) {
	using namespace std;
	if (_game.__dealer.dealerStatus == Status::PROGRESS && _game.__player.playerStatus == Status::PROGRESS && _game.__gameStatus == GameStatus::FINISHING) {
		if (_game.__dealer.getDealerCount() == _game.__player.getPlayerCount()) {
			setPlayerStatus(_game.__dealer.dealerStatus, Status::DEALER_WIN);
			setPlayerStatus(_game.__player.playerStatus, Status::PLAYER_WIN);
			setGameStatus(_game, GameStatus::TIE);
			return _game.__gameStatus;
		}
		else if (_game.__dealer.getDealerCount() < _game.__player.getPlayerCount()) {
			setPlayerStatus(_game.__dealer.dealerStatus, Status::BUST);
			setPlayerStatus(_game.__player.playerStatus, Status::PLAYER_WIN);
			setGameStatus(_game, GameStatus::PLAYER_WIN);
			return _game.__gameStatus;
		}
		else {
			setPlayerStatus(_game.__dealer.dealerStatus, Status::DEALER_WIN);
			setPlayerStatus(_game.__player.playerStatus, Status::BUST);
			setGameStatus(_game, GameStatus::DEALER_WIN);
			return _game.__gameStatus;
		}
	}
	if (_game.__dealer.getDealerCount() == 21 && _game.__dealer.dealerStatus != Status::BLACKJACK && _game.__dealerSession == 0){
		cout << "\nDealer's Hit BlackJack!" << endl;
		setPlayerStatus(_game.__dealer.dealerStatus, Status::BLACKJACK);
	}
	else if (_game.__dealer.getDealerCount() > 21 && _game.__dealer.dealerStatus != Status::BUST) {
		cout << "\nDealer's Busted Out!" << endl;
		setPlayerStatus(_game.__dealer.dealerStatus, Status::BUST);
	}

	if (_game.__player.getPlayerCount() == 21 && _game.__player.playerStatus != Status::BLACKJACK && _game.__playerSession == 0) {
		cout << "\nPlayer's Hit BlackJack!" << endl;
		setPlayerStatus(_game.__player.playerStatus, Status::BLACKJACK);
		_balance.updateBalance(_balance, _game.__player.playerStake * 2.5);
		cout << "\nYour balance is: " << _balance.getBalance(_balance) << endl;
	}
	else if (_game.__player.getPlayerCount() > 21 && _game.__player.playerStatus != Status::BUST) {
		cout << "\nPlayer's Busted Out!" << endl;
		setPlayerStatus(_game.__player.playerStatus, Status::BUST);
	}
	return checkGameStatus(_game);
}

GameStatus Game::checkGameStatus(Game& _game) {
	if (_game.__gameStatus != GameStatus::PROGRESS) return _game.__gameStatus;
	if (_game.__dealer.dealerStatus == Status::BLACKJACK && _game.__player.playerStatus == Status::BLACKJACK) {
		setGameStatus(_game, GameStatus::TIE);
		return GameStatus::TIE;
	}
	else if (_game.__dealer.dealerStatus == Status::BUST || _game.__player.playerStatus == Status::PLAYER_WIN || _game.__player.playerStatus == Status::BLACKJACK) {
		setGameStatus(_game, GameStatus::PLAYER_WIN);
		return GameStatus::PLAYER_WIN;
	}
	else if (_game.__player.playerStatus == Status::BUST || _game.__dealer.dealerStatus == Status::DEALER_WIN || _game.__dealer.dealerStatus == Status::BLACKJACK) {
		setGameStatus(_game, GameStatus::DEALER_WIN);
		return GameStatus::DEALER_WIN;
	};
	setGameStatus(_game, GameStatus::PROGRESS);
	return GameStatus::PROGRESS;
}

GameStatus Game::startGame(Game& _game, bool& _session, Balance& _balance) {
	if (_game.__currentSession) {
		if (checkPlayersScores(_game, _balance) != GameStatus::PROGRESS) return _game.__gameStatus;
		std::cout << "\nPlayer's Turn:\n";
		doActionPlayer(_game, _balance);
		__balanceAce(_game, _game.__balanceNeed);

		if (_game.__gameStatus == GameStatus::PROGRESS) {
			std::cout << "\nDealer's Turn:\n";
			doActionDealer(_game, _balance);
			__balanceAce(_game, _game.__balanceNeed);
		}
		if (_game.__gameStatus == GameStatus::PROGRESS) {
			setGameStatus(_game, GameStatus::FINISHING);
		}
		gameEnder(_game, _session, _balance);
	}
}

void Game::gameEnder(Game& _game, bool& _session, Balance& _balance) {
	if (_game.__currentSession) {
		checkPlayersScores(_game, _balance);
		__endGameOutput(_game, _game.__gameStatus, _balance);
		_game.__currentSession = setSession(_session, false);
		setPlayerStatus(_game.__dealer.dealerStatus, Status::FINISHED);
		setPlayerStatus(_game.__player.playerStatus, Status::FINISHED);
		setGameStatus(_game, GameStatus::FINISHED);
	}
}

void Game::__endGameOutput(Game& _game, GameStatus status, Balance& _balance) {
	using namespace std;
	switch (status)
	{
	case GameStatus::DEALER_WIN:
		cout << "\nThe Dealer Won! Dealer's score: " << _game.__dealer.getDealerCount();
		cout << "\nPlayer's Score: " << _game.__player.getPlayerCount() << endl;
		break;
	case GameStatus::PLAYER_WIN:
		cout << "\nThe Player Won! Player's Score: " << _game.__player.getPlayerCount();
		cout << "\nDealer's score: " << _game.__dealer.getDealerCount() << endl;
		if(_game.__player.playerStatus != Status::BLACKJACK) _balance.updateBalance(_balance, _game.__player.playerStake * 2);
		break;
	case GameStatus::TIE:
		cout << "\nGame ended in Tie! Dealer's score: " << _game.__dealer.getDealerCount();
		cout << "\nPlayer's Score: " << _game.__player.getPlayerCount() << endl;
		_balance.updateBalance(_balance, _game.__player.playerStake);
		break;
	default:
		break;
	}
	cout << "\nYour balance is: " << _balance.getBalance(_balance) << endl;
}


GameStatus Game::doActionPlayer(Game& _game, Balance& _balance) {
	using namespace std;
	cout << "\nChoose next action: \n1. Hit\n2. Stand\n3. Double Down\n4. Split\nEnter number: ";
	int action;
	cin >> action;
	Actions actionType = getActionType(action);
	switch (actionType)
	{
	case Actions::HIT: {
		Card newCard = _game.__player.hitMovePlayer(_game.__deck);
		cout << "\nPlayer got: " << newCard.name << " of " << newCard.suit << ". Cost: " << newCard.value << std::endl;
		//("/" + newCard.addValue ? newCard.shortName == "A" : "")
		__checkForAce(_game);
		__balanceAce(_game, _game.__balanceNeed);
		_game.__playerSession++;
		_game.__player.getPlayerHand();
		std::cout << "Player: '" << _game.__player.getPlayerName() << "' count: " << _game.__player.getPlayerCount() << std::endl;
		if (checkPlayersScores(_game, _balance) != GameStatus::PROGRESS) return _game.__gameStatus;
		else return doActionPlayer(_game, _balance);
		break;
	}
	case Actions::STAND:
		cout << "You chose to stand!\n";
		break;
	case Actions::DOUBLE_DOWN:
		break;
	case Actions::SPLIT:
		break;
	default:
		cerr << "\nWrong Action! Try again!";
		return doActionPlayer(_game, _balance);
		break;
	}
}

GameStatus Game::doActionDealer(Game& _game, Balance& _balance) {
	using namespace std;
	int action;
	short dealersCount = _game.__dealer.getDealerCount();
	if (dealersCount == 17 && _game.__balanceNeed == true) {
		for (auto& card : _game.__dealer.getDealerHand(true)) {
			if (card.shortName == "A" && card.value == 11) action = 1;
		}
	}
	if (dealersCount > 16) {
		action = 2;
	} else action = 1;
	Actions actionType = getActionType(action);
	switch (actionType)
	{
	case Actions::HIT: {
		Card newCard = _game.__dealer.hitMoveDealer(_game.__deck);
		cout << "\nDealer got: " << newCard.name << " of " << newCard.suit << ". Cost: " << newCard.value << std::endl;
		//("/" + newCard.addValue ? newCard.shortName == "A" : "")
		__checkForAce(_game);
		__balanceAce(_game, _game.__balanceNeed);
		_game.__dealer.getDealerHand();
		std::cout << "Dealer: count: " << _game.__dealer.getDealerCount() << std::endl;
		_game.__dealerSession++;
		if (checkPlayersScores(_game, _balance) != GameStatus::PROGRESS) return _game.__gameStatus;
		else return doActionDealer(_game, _balance);
		break;
	}
	case Actions::STAND:
		if (_game.__dealerSession == 0) {
			_game.__dealer.getDealerHand();
			std::cout << "Dealer: count: " << _game.__dealer.getDealerCount() << std::endl;
		}
		break;
	default:
		return doActionDealer(_game, _balance);
		break;
	}
}


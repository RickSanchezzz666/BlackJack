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

void Game::setSplitStatus(SplitStatus& status, SplitStatus statusType) {
	status = statusType;
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
	if (!(std::cin >> stake)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

bool Game::__checkStake(Game& _game, Balance& _balance) {
	return _balance.checkBalance(_balance, _game.__player.playerStake);
}

void Game::updateHandCount(Card card, int& counter) {
	counter += card.value;
}

void Game::updateHandCount(int aceValue, int& counter) {
	if (aceValue == 1) {
		counter -= 10;
	}
}

void Game::updateHandCount(int val, int& counter, bool split) {
	counter += val;
}

bool Game::__checkForAce(Game& _game, bool split) {
	if (!_game.__balanceNeed) {
		if (split) {
			for (auto x : _game.__player.getPlayerHand(true, true)) {
				if (x.shortName == "A") {
					_game.__balanceNeed = true;
					return _game.__balanceNeed;
				}
			}
		}
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

void Game::__swapAceValues(Game& _game, int player, bool split) {
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
		if (split) {
			for (auto& card : _game.__player.getPlayerHand(true, true)) {
				if (card.shortName == "A") {
					int playerCount = _game.__player.getPlayerCount(true);
					if (playerCount > 21 && card.value == 11) {
						card.value = 1;
						_game.__player.updatePlayerCount(card.value, true);
					}
				}
			}
		}
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

void Game::__balanceAce(Game& _game, bool& balanceNeed, bool split) {
	if (balanceNeed) {
		int dealerCount = _game.__dealer.getDealerCount();
		if (dealerCount > 21) {
			_game.__swapAceValues(_game, 0);
		}

		int playerCount = _game.__player.getPlayerCount();
		if (playerCount > 21) {
			_game.__swapAceValues(_game, 1);
		}

		if (split) {
			int splitCount = _game.__player.getPlayerCount(true);
			if (splitCount > 21) {
				_game.__swapAceValues(_game, 1, split);
			}
		}
	}
}

void Game::prepareGame(Game &_game, bool &_session, Balance& _balance, std::string& name) {
	using namespace std;
	cout << "Hi " << name << ", now we are gonna start the game!\n";
	cout << "Your balance is: " << getBalance(_balance) << std::endl;
	_game = createGame(name, _balance);

	__checkForAce(_game);
	__balanceAce(_game, _game.__balanceNeed);
	_game.__currentSession = setSession(_session, true);
	_game.doubleDownStatus = false;
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


GameStatus Game::checkPlayersScores(Game& _game, Balance& _balance, bool split) {
	using namespace std;
	if (_game.__dealer.dealerStatus == Status::PROGRESS && _game.__player.playerStatus == Status::PROGRESS && _game.__gameStatus == GameStatus::FINISHING) {
		if (_game.__dealer.getDealerCount() == _game.__player.getPlayerCount() && _game.__dealer.getDealerCount() == _game.__player.getPlayerCount(true)) {
			setPlayerStatus(_game.__dealer.dealerStatus, Status::DEALER_WIN);
			setPlayerStatus(_game.__player.playerStatus, Status::PLAYER_WIN);
			setSplitStatus(_game.__player.splitStatus[0], SplitStatus::FIRST_WIN);
			setSplitStatus(_game.__player.splitStatus[1], SplitStatus::SECOND_WIN);
			setGameStatus(_game, GameStatus::TIE);
			return _game.__gameStatus;
		}
		else if (_game.__dealer.getDealerCount() < _game.__player.getPlayerCount() && _game.__player.splitStatus[0] != SplitStatus::FIRST_BUST) {
			setPlayerStatus(_game.__dealer.dealerStatus, Status::BUST);
			setPlayerStatus(_game.__player.playerStatus, Status::PLAYER_WIN);
			setSplitStatus(_game.__player.splitStatus[0], SplitStatus::FIRST_WIN);
		}
		else if (_game.__dealer.getDealerCount() < _game.__player.getPlayerCount(true) && _game.__player.splitStatus[1] != SplitStatus::FIRST_BUST) {
			setPlayerStatus(_game.__dealer.dealerStatus, Status::BUST);
			setPlayerStatus(_game.__player.playerStatus, Status::PLAYER_WIN);
			setSplitStatus(_game.__player.splitStatus[1], SplitStatus::SECOND_WIN);
		}
		else {
			setPlayerStatus(_game.__dealer.dealerStatus, Status::DEALER_WIN);
			setPlayerStatus(_game.__player.playerStatus, Status::BUST);
			setSplitStatus(_game.__player.splitStatus[0], SplitStatus::FIRST_BUST);
			setSplitStatus(_game.__player.splitStatus[1], SplitStatus::SECOND_BUST);
			setGameStatus(_game, GameStatus::DEALER_WIN);
		}
		return _game.__gameStatus;
	}

	if (_game.__player.getPlayerCount() <= 21 && _game.__player.splitStatus[0] == SplitStatus::PROGRESS) {
		setSplitStatus(_game.__player.splitStatus[0], SplitStatus::FIRST_WIN);
	} 
	else if (_game.__player.getPlayerCount(true) <= 21 && _game.__player.splitStatus[1] == SplitStatus::PROGRESS) {
		setSplitStatus(_game.__player.splitStatus[1], SplitStatus::SECOND_WIN);
	}
	else if (_game.__player.getPlayerCount() > 21) {
		setSplitStatus(_game.__player.splitStatus[0], SplitStatus::FIRST_BUST);
	}
	else if (_game.__player.getPlayerCount(true) > 21) {
		setSplitStatus(_game.__player.splitStatus[1], SplitStatus::SECOND_BUST);
	}
	return checkGameStatus(_game, split);
}

GameStatus Game::checkGameStatus(Game& _game, bool split) {
	if (_game.__gameStatus != GameStatus::PROGRESS) return _game.__gameStatus;
	else if (_game.__dealer.dealerStatus == Status::DEALER_WIN && _game.__player.playerStatus == Status::PLAYER_WIN) {
		setGameStatus(_game, GameStatus::TIE);
		return GameStatus::TIE;
	}
	else if (_game.__dealer.dealerStatus == Status::BUST && _game.__player.playerStatus == Status::PLAYER_WIN && (_game.__player.splitStatus[0] == SplitStatus::FIRST_WIN || _game.__player.splitStatus[1] == SplitStatus::SECOND_WIN)) {
		setGameStatus(_game, GameStatus::PLAYER_WIN);
		return GameStatus::PLAYER_WIN;
	}
	else if (_game.__dealer.dealerStatus == Status::DEALER_WIN || _game.__player.splitStatus[0] == SplitStatus::FIRST_BUST || _game.__player.splitStatus[1] == SplitStatus::SECOND_BUST) {
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
			_game.__dealer.getDealerCard(__deck);
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
		if (_game.splitStatus) {
			checkPlayersScores(_game, _balance, _game.splitStatus);
			__endGameOutput(_game, _game.__gameStatus, _balance, _game.splitStatus);
		}
		else {
			checkPlayersScores(_game, _balance);
			__endGameOutput(_game, _game.__gameStatus, _balance, _game.splitStatus);
		}
		_game.__currentSession = setSession(_session, false);
		setPlayerStatus(_game.__dealer.dealerStatus, Status::FINISHED);
		setPlayerStatus(_game.__player.playerStatus, Status::FINISHED);
		setGameStatus(_game, GameStatus::FINISHED);
	}
}

void Game::__endGameOutput(Game& _game, GameStatus status, Balance& _balance, bool split) {
	using namespace std;
	if (split) {
		if (split) {
			if (_game.__player.splitStatus[0] == SplitStatus::FIRST_BUST && _game.__player.splitStatus[1] == SplitStatus::SECOND_BUST) {
				cout << "\nThe Dealer Won! Dealer's score: " << _game.__dealer.getDealerCount();
				cout << "\nFirst hand lost! With score: " << _game.__player.getPlayerCount() << endl;
				cout << "\nSecond hand lost! With score: " << _game.__player.getPlayerCount(true) << endl;
			}
			else {
				float multiplier = 1.0f;
				if (_game.__player.splitStatus[0] == SplitStatus::FIRST_WIN) {
					if (_game.__player.getPlayerCount() == _game.__dealer.getDealerCount()) {
						cout << "\nFirst hand ended in Tie! With score: " << _game.__player.getPlayerCount() << endl;
					}
					else {
						cout << "\nFirst hand won! With score: " << _game.__player.getPlayerCount() << endl;
						multiplier += 0.5;
					}
				}
				else if (_game.__player.splitStatus[0] == SplitStatus::FIRST_BUST) {
					cout << "\nFirst hand lost! With score: " << _game.__player.getPlayerCount() << endl;
				}
				if (_game.__player.splitStatus[1] == SplitStatus::SECOND_WIN) {
					if (_game.__player.getPlayerCount(true) == _game.__dealer.getDealerCount()) {
						cout << "\Second hand ended in Tie! With score: " << _game.__player.getPlayerCount(true) << endl;
					}
					else {
						cout << "\nSecond hand won! With score: " << _game.__player.getPlayerCount(true) << endl;
						multiplier += 0.5;
					}
				}
				else if (_game.__player.splitStatus[1] == SplitStatus::SECOND_BUST) {
					cout << "\nSecond hand lost! With score: " << _game.__player.getPlayerCount(true) << endl;
				}
				cout << "\nDealer's score: " << _game.__dealer.getDealerCount();
				_balance.updateBalance(_balance, _game.__player.playerStake * multiplier);
			}
		}
	}
	else {
		switch (status)
		{
		case GameStatus::DEALER_WIN:
			cout << "\nThe Dealer Won! Dealer's score: " << _game.__dealer.getDealerCount();
			cout << "\nPlayer's Score: " << _game.__player.getPlayerCount() << endl;
			break;
		case GameStatus::PLAYER_WIN:
			cout << "\nThe Player Won! Player's Score: " << _game.__player.getPlayerCount();
			cout << "\nDealer's score: " << _game.__dealer.getDealerCount() << endl;
			if (_game.__player.playerStatus != Status::BLACKJACK) _balance.updateBalance(_balance, _game.__player.playerStake * 2);
		break;
		case GameStatus::TIE:
			cout << "\nGame ended in Tie! Dealer's score: " << _game.__dealer.getDealerCount();
			cout << "\nPlayer's Score: " << _game.__player.getPlayerCount() << endl;
			_balance.updateBalance(_balance, _game.__player.playerStake);
			break;
		default:
			break;
		}
	}
	cout << "\nYour balance is: " << _balance.getBalance(_balance) << endl;
}


GameStatus Game::doActionPlayerSplit(Game& _game, Balance& _balance, int player, int action) {
	using namespace std;
	int firstHand;
	int secondHand;
	if (player == 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "\nChoose next action to First Hand: \n1. Hit\n2. Stand\nEnter number: ";
		cin >> firstHand;
		action = firstHand;
	}
	else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "\nChoose next action to Second Hand: \n1. Hit\n2. Stand\nEnter number: ";
		cin >> secondHand;
		action = secondHand;
	}

	Actions actionType = getActionType(action);
	switch (actionType)
	{
	case Actions::HIT: {
		if (player == 0) {
			Card newCard = _game.__player.hitMovePlayer(_game.__deck);
			cout << "\nPlayer got: " << newCard.name << " of " << newCard.suit << ". Cost: " << newCard.value << endl;
			__checkForAce(_game, true);
			__balanceAce(_game, _game.__balanceNeed, true);
			_game.__playerSession++;
			_game.__player.getPlayerHand();
			cout << "Player: '" << _game.__player.getPlayerName() << "' First hand count: " << _game.__player.getPlayerCount() << endl;
			if (_game.__player.getPlayerCount() > 21) {
				cout << "\nPlayer's First hand Busted Out!" << endl;
				return doActionPlayerSplit(_game, _balance, player + 1);
			}
			if (checkPlayersScores(_game, _balance, true) != GameStatus::PROGRESS) return doActionPlayerSplit(_game, _balance, player + 1);
			else return doActionPlayerSplit(_game, _balance, player);
		}
		else {
			Card newCard = _game.__player.hitMovePlayer(_game.__deck, true);
			cout << "\nPlayer got: " << newCard.name << " of " << newCard.suit << ". Cost: " << newCard.value << endl;
			__checkForAce(_game, true);
			__balanceAce(_game, _game.__balanceNeed, true);
			_game.__playerSession++;
			_game.__player.getPlayerAddHand();
			cout << "Player: '" << _game.__player.getPlayerName() << "' Second hand count: " << _game.__player.getPlayerCount(true) << endl;
			if (_game.__player.getPlayerCount(true) > 21) {
				cout << "\nPlayer's Second hand Busted Out!" << endl;
				return _game.__gameStatus;
			}
			if (checkPlayersScores(_game, _balance, true) != GameStatus::PROGRESS) return _game.__gameStatus;
			else return doActionPlayerSplit(_game, _balance, player);
		}
		break;
	}
	case Actions::STAND:
		if (player == 0) {
			cout << "\nFirst hand choosed to stand!\n";
			return doActionPlayerSplit(_game, _balance, player + 1);
		}
		else {
			cout << "\nSecond hand choosed to stand!\n";
			return _game.__gameStatus;
		}
		break;
	default:
		cerr << "\nWrong Action! Try again!";
		return doActionPlayerSplit(_game, _balance, player);
		break;
	}
}


GameStatus Game::doActionPlayer(Game& _game, Balance& _balance, int action) {
	using namespace std;
	if (action == -1) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "\nChoose next action: \n1. Hit\n2. Stand\n3. Double Down\n4. Split\nEnter number: ";
		cin >> action;
	}
	Actions actionType = getActionType(action);
	switch (actionType)
	{
	case Actions::HIT: {
		Card newCard = _game.__player.hitMovePlayer(_game.__deck);
		cout << "\nPlayer got: " << newCard.name << " of " << newCard.suit << ". Cost: " << newCard.value << endl;
		//("/" + newCard.addValue ? newCard.shortName == "A" : "")
		__checkForAce(_game);
		__balanceAce(_game, _game.__balanceNeed);
		_game.__playerSession++;
		_game.__player.getPlayerHand();
		cout << "Player: '" << _game.__player.getPlayerName() << "' count: " << _game.__player.getPlayerCount() << endl;
		if (checkPlayersScores(_game, _balance) != GameStatus::PROGRESS || _game.doubleDownStatus == true) return _game.__gameStatus;
		else return doActionPlayer(_game, _balance);
		break;
	}
	case Actions::STAND:
		cout << "You chose to stand!\n";
		__checkForAce(_game);
		__balanceAce(_game, _game.__balanceNeed);
		break;
	case Actions::DOUBLE_DOWN: {
		if (!__checkStake(_game, _balance)) {
			cerr << "\nNot enough money to Double Down! Try again!";
			return doActionPlayer(_game, _balance);
		}
		cout << "\nPlayer choosed to Double Down!\n";
		_balance.updateBalance(_balance, -_game.__player.playerStake);
		_game.__player.playerStake *= 2;
		_game.doubleDownStatus = true;
		_game.__playerSession++;
		return doActionPlayer(_game, _balance, 1);
		break;
	}
	case Actions::SPLIT: {
		if (_game.__player.getHandSize() != 2) {
			cerr << "\nYou should have only 2 cards to split! Try again!";
			return doActionPlayer(_game, _balance);
		}
		std::vector<Card> hand = _game.__player.getPlayerHand(true);
		if (hand[0].value != hand[1].value && (hand[0].shortName != "A" && hand[1].shortName != "A")) {
			cerr << "\nYou should have 2 equally vallued cards to split! Try again!";
			return doActionPlayer(_game, _balance);
		}
		cout << "\nPlayer choosed to Split!\n";
		_balance.updateBalance(_balance, -_game.__player.playerStake);
		_game.__player.playerStake *= 2;
		_game.splitStatus = true;
		_game.__player.splitMove();
		doActionPlayerSplit(_game, _balance, 0);
		_game.__player.getPlayerHand();
		cout << "Player: '" << _game.__player.getPlayerName() << "' First hand count: " << _game.__player.getPlayerCount() << endl;
		_game.__player.getPlayerAddHand();
		cout << "Player: '" << _game.__player.getPlayerName() << "' Second hand count: " << _game.__player.getPlayerCount(true) << endl;
		break;
	}
	default:
		cerr << "\nWrong Action! Try again!";
		return doActionPlayer(_game, _balance);
		break;
	}
}

GameStatus Game::doActionDealer(Game& _game, Balance& _balance) {
	using namespace std;
	int action;
	__checkForAce(_game);
	__balanceAce(_game, _game.__balanceNeed);
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


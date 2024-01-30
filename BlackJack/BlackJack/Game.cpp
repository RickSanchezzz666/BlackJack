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

Game::Game(std::string name) {
	if (!name.empty()) {
		__deck = Deck();
		__dealer = Dealer(__deck);
		__player = Player(__deck, name);
	}
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
		for (auto card : _game.__dealer.getDealerHand(true)) {
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
		for (auto card : _game.__player.getPlayerHand(true)) {
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

void Game::prepareGame(Game &_game, bool &_session) {
	using namespace std;
	cout << "Welcome to game BlackJack!\nEnter your name please: ";
	string name = "";
	cin >> name;
	cout << "Hi " << name << ", now we are gonna start the first game!\n";
	cout << "Your initial balance is: " << getBalance() << std::endl;
	_game = createGame(name);
	__checkForAce(_game);
	__balanceAce(_game, _game.__balanceNeed);
	_game.__currentSession = setSession(_session, true);
	setPlayerStatus(_game.__dealer.dealerStatus, Status::PROGRESS);
	setPlayerStatus(_game.__player.playerStatus, Status::PROGRESS);
	setGameStatus(_game, GameStatus::PROGRESS);
	startGame(_game);
}

Game Game::createGame(std::string& name) {
	Game game(name);
	return game;
}


GameStatus Game::checkPlayersScores(Game& _game) {
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
	if (_game.__dealer.getDealerCount() == 21 && _game.__dealer.dealerStatus != Status::BLACKJACK) {
		cout << "\nDealer's Hit BlackJack!" << endl;
		setPlayerStatus(_game.__dealer.dealerStatus, Status::BLACKJACK);
	}
	else if (_game.__dealer.getDealerCount() > 21 && _game.__dealer.dealerStatus != Status::BUST) {
		cout << "\nDealer's Busted Out!" << endl;
		setPlayerStatus(_game.__dealer.dealerStatus, Status::BUST);
	}

	if (_game.__player.getPlayerCount() == 21 && _game.__player.playerStatus != Status::BLACKJACK) {
		cout << "\nPlayer's Hit BlackJack!" << endl;
		setPlayerStatus(_game.__player.playerStatus, Status::BLACKJACK);
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

GameStatus Game::startGame(Game& _game) {
	if (_game.__currentSession) {
		if (checkPlayersScores(_game) != GameStatus::PROGRESS) return _game.__gameStatus;
		std::cout << "\nPlayer's Turn:\n";
		doActionPlayer(_game);
		__balanceAce(_game, _game.__balanceNeed);

		if (_game.__gameStatus == GameStatus::PROGRESS) {
			std::cout << "\nDealer's Turn:\n";
			//doActionDealer();
			__balanceAce(_game, _game.__balanceNeed);
		}
		if (_game.__gameStatus == GameStatus::PROGRESS) {
			setGameStatus(_game, GameStatus::FINISHING);
		}
		gameEnder(_game);
	}
}

void Game::gameEnder(Game& _game) {
	if (_game.__currentSession) {
		checkPlayersScores(_game);
		__endGameOutput(_game, _game.__gameStatus);
	}
}

void Game::__endGameOutput(Game& _game, GameStatus status) {
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
		break;
	case GameStatus::TIE:
		cout << "\nGame ended in Tie! Dealer's score: " << _game.__dealer.getDealerCount();
		cout << "\nPlayer's Score: " << _game.__player.getPlayerCount() << endl;
		break;
	default:
		break;
	}
}


GameStatus Game::doActionPlayer(Game& _game) {
	using namespace std;
	cout << "\nChoose next action: \n1. Hit\n2. Stand\n3. Double Down\n4. Split\nEnter number: ";
	short action;
	cin >> action;
	Actions actionType = getActionType(action);
	switch (actionType)
	{
	case Actions::HIT: {
		Card newCard = _game.__player.hitMovePlayer(__deck);
		cout << "\nYou got: " << newCard.name << " of " << newCard.suit << ". Cost: " << newCard.value << std::endl;
		//("/" + newCard.addValue ? newCard.shortName == "A" : "")
		__checkForAce(_game);
		__balanceAce(_game, _game.__balanceNeed);
		_game.__player.getPlayerHand();
		std::cout << "Player: '" << _game.__player.getPlayerName() << "' count: " << _game.__player.getPlayerCount() << std::endl;
		if (checkPlayersScores(_game) != GameStatus::PROGRESS) return _game.__gameStatus;
		else return doActionPlayer(_game);
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
		return doActionPlayer(_game);
		break;
	}
}

/*GameStatus Game::doActionDealer(Game& _game) {
	using namespace std;
	short action;
	Actions actionType = getActionType(action);
	switch (actionType)
	{
	case Actions::HIT: {
		Card newCard = _game.__player.hitMovePlayer(__deck);
		cout << "\nYou got: " << newCard.name << " of " << newCard.suit << ". Cost: " << newCard.value << std::endl;
		_game.__player.getPlayerHand();
		std::cout << "Player: '" << _game.__player.getPlayerName() << "' count: " << _game.__player.getPlayerCount() << std::endl;
		if (checkPlayersScores(_game) != GameStatus::PROGRESS) return _game.__gameStatus;
		else return doActionPlayer(_game);
		break;
	}
	case Actions::STAND:
		cout << "You chose to stand!\n";
		break;
	case Actions::DOUBLE_DOWN:
		break;
	case Actions::SPLIT:
		break;
	}
}*/


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

void Game::prepareGame(Game &_game, bool &_session) {
	using namespace std;
	cout << "Welcome to game BlackJack!\nEnter your name please: ";
	string name = "";
	cin >> name;
	cout << "Hi " << name << ", now we are gonna start the first game!\n";
	cout << "Your initial balance is: " << getBalance() << std::endl;
	_game = createGame(name);
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

GameStatus Game::startGame(Game& _game) {
	if (_game.__currentSession) {
		if (checkPlayersScores(_game) != GameStatus::PROGRESS) return _game.__gameStatus;
		try {
			doActionPlayer(_game);
		}
		catch (std::string& err) {
			std::cerr << err << "Choose again!";
			doActionPlayer(_game);
		}
		if (_game.__gameStatus == GameStatus::PROGRESS) {
			//doActionDealer();
		}

	}
}

GameStatus Game::checkPlayersScores(Game& _game) {
	if (_game.__dealer.getDealerCount() == 21) {
		setPlayerStatus(_game.__dealer.dealerStatus, Status::BLACKJACK);
	}
	else if (_game.__dealer.getDealerCount() > 21) {
		setPlayerStatus(_game.__dealer.dealerStatus, Status::BUST);
	}

	if (_game.__player.getPlayerCount() == 21) {
		setPlayerStatus(_game.__player.playerStatus, Status::BLACKJACK);
	}
	else if (_game.__player.getPlayerCount() > 21) {
		setPlayerStatus(_game.__player.playerStatus, Status::BUST);
	}
	return checkGameStatus(_game);
}

GameStatus Game::checkGameStatus(Game& _game) {
	if (_game.__dealer.dealerStatus == Status::BLACKJACK && _game.__player.playerStatus == Status::BLACKJACK) {
		setGameStatus(_game, GameStatus::TIE);
		return GameStatus::TIE;
	}
	else if (_game.__dealer.dealerStatus == Status::BUST) {
		setGameStatus(_game, GameStatus::PLAYER_WIN);
		return GameStatus::PLAYER_WIN;
	}
	else if (_game.__player.playerStatus == Status::BUST) {
		setGameStatus(_game, GameStatus::DEALER_WIN);
		return GameStatus::DEALER_WIN;
	};
	setGameStatus(_game, GameStatus::PROGRESS);
	return GameStatus::PROGRESS;
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
		cout << "You got: " << newCard.name << " of " << newCard.suit << ". Cost: " << newCard.value << std::endl;
		_game.__player.getPlayerHand();
		std::cout << "Player: '" << _game.__player.getPlayerName() << "' count: " << _game.__player.getPlayerCount() << std::endl;
		if (checkPlayersScores(_game) != GameStatus::PROGRESS) return _game.__gameStatus;
		else return doActionPlayer(_game);
		break;
	}
	case Actions::STAND:
		cout << "You chose to stand!\n";
		//GAME ENDER
		break;
	case Actions::DOUBLE_DOWN:
		break;
	case Actions::SPLIT:
		break;
	default:
		throw("Wrong action!");
		break;
	}
}

void Game::doActionDealer() {
	using namespace std;
}


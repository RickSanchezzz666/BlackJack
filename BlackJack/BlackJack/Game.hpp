#pragma once
#include "Deck.hpp"
#include "Dealer.hpp"
#include "Player.hpp"
#include "Actions.hpp"
#include "Status.hpp"

#include <string>

enum class GameStatus {
	FINISHED,
	PROGRESS,
	FINISHING,
	DEALER_WIN,
	PLAYER_WIN,
	TIE
};

class Game : public Dealer, public Player {
private:
	Deck __deck;
	Dealer __dealer;
	Player __player;

	int __currentSession = false;

	void setPlayerStatus(Status &player, Status statusType);
	void setGameStatus(Game& _game, GameStatus statusType);

	bool setSession(bool& _session, bool type);

	void __endGameOutput(Game& _game, GameStatus status);

	void __swapAceValues(Game& _game, int player);

	bool __checkForAce(Game& _game);
	void __balanceAce(Game& _game, bool& balanceNeed);

	bool __balanceNeed = false;


public:
	Game() : __gameStatus(GameStatus::FINISHED) {};

	Game(std::string name);

	GameStatus __gameStatus = GameStatus::FINISHED;

	GameStatus doActionPlayer(Game& _game);

	GameStatus doActionDealer(Game& _game);

	GameStatus checkPlayersScores(Game& _game);

	void gameEnder(Game& _game);

	GameStatus checkGameStatus(Game& _game);

	static void updateHandCount(Card card, int& counter);
	static void updateHandCount(int aceValue, int& counter);

	void prepareGame(Game& _game, bool& _session);

	Game createGame(std::string& name);

	GameStatus startGame(Game& _game);
};
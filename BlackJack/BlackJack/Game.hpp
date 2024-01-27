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

	void doActionDealer();

	void setPlayerStatus(Status &player, Status statusType);
	void setGameStatus(Game& _game, GameStatus statusType);

	bool setSession(bool& _session, bool type);


public:
	Game() : __gameStatus(GameStatus::FINISHED) {};

	Game(std::string name);

	GameStatus __gameStatus = GameStatus::FINISHED;

	GameStatus doActionPlayer(Game& _game);

	GameStatus checkPlayersScores(Game& _game);

	GameStatus checkGameStatus(Game& _game);

	static void updateHandCount(Card card, int& counter);

	void prepareGame(Game& _game, bool& _session);

	Game createGame(std::string& name);

	GameStatus startGame(Game& _game);
};
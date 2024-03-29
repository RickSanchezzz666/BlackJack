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

	int __dealerSession = 0;
	int __playerSession = 0;

	bool doubleDownStatus = false;
	bool splitStatus = false;

	void setPlayerStatus(Status &player, Status statusType);
	void setSplitStatus(SplitStatus& status, SplitStatus statusType);
	void setGameStatus(Game& _game, GameStatus statusType);

	bool setSession(bool& _session, bool type);

	void __endGameOutput(Game& _game, GameStatus status, Balance& _balance, bool split);

	void __swapAceValues(Game& _game, int player, bool split = false);

	bool __checkForAce(Game& _game, bool split = false);
	void __balanceAce(Game& _game, bool& balanceNeed, bool split = false);

	int __checkStake(Balance& _balance);
	bool __checkStake(Game& _game, Balance& _balance);

	bool __balanceNeed = false;


public:
	Game() : __gameStatus(GameStatus::FINISHED) {};

	Game(std::string name, Balance& _balance);

	GameStatus __gameStatus = GameStatus::FINISHED;

	GameStatus doActionPlayer(Game& _game, Balance& _balance, int action = -1);

	GameStatus doActionPlayerSplit(Game& _game, Balance& _balance, int player, int action = -1);

	GameStatus doActionDealer(Game& _game, Balance& _balance);

	GameStatus checkPlayersScores(Game& _game, Balance& _balance);
	GameStatus checkPlayersScores(Game& _game, Balance& _balance, bool split);

	void gameEnder(Game& _game, bool& _session, Balance& _balance);

	GameStatus checkGameStatus(Game& _game);
	GameStatus checkGameStatus(Game& _game, bool split);

	static void updateHandCount(Card card, int& counter);
	static void updateHandCount(int aceValue, int& counter);
	static void updateHandCount(int val, int& counter, bool split);

	void prepareGame(Game& _game, bool& _session, Balance& _balance, std::string& _name);

	Game createGame(std::string& name, Balance& _balance);

	GameStatus startGame(Game& _game, bool& _session, Balance& _balance);
};
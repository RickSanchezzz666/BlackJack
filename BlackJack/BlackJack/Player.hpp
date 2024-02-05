#pragma once
#include "Deck.hpp"
#include "Balance.hpp"
#include "Status.hpp"

#include <vector>
#include <string>

class Player : public Balance {
protected:
	int _scoreCounter = 0;
	int _addScoreCounter = 0;
	std::vector<Card> hand;
	std::vector<Card> addHand = {};

	std::string _name = "";

	void __updateStake(int stake);

	void __makeStake(Balance& _balance, int stake);

public:
	int playerStake = 0;

	Status playerStatus;

	SplitStatus splitStatus[2] = { SplitStatus::PROGRESS, SplitStatus::PROGRESS };

	Player() : hand({}), playerStatus(Status::FINISHED) {};

	Player(Deck& deck, std::string& name, Balance& _balance, int stake);

	void setPlayerName(std::string& name);

	void getPlayerCard(Deck& deck);
	void getPlayerCard(Deck& deck, bool split);

	int getHandSize();

	
	void updatePlayerCount(int val);
	void updatePlayerCount(int val, bool split);

	std::vector<Card>& getPlayerHand(bool aceCheck);
	std::vector<Card>& getPlayerHand(bool aceCheck, bool split);
	void getPlayerHand();
	void getPlayerAddHand();
	int getPlayerCount();
	int getPlayerCount(bool split);

	std::string getPlayerName();

	Card hitMovePlayer(Deck& deck);
	Card hitMovePlayer(Deck& deck, bool split);

	void splitMove();
};
#pragma once
#include "Deck.hpp"
#include "Balance.hpp"
#include "Status.hpp"

#include <vector>
#include <string>

class Player : public Balance {
protected:
	int _scoreCounter = 0;
	std::vector<Card> hand;

	std::string _name = "";

	void __updateStake(int stake);

	void __makeStake();

public:
	Balance balance;

	int playerStake = 0;

	Status playerStatus;

	Player() : hand({}), playerStatus(Status::FINISHED) {};

	Player(Deck& deck, std::string& name);

	void setPlayerName(std::string& name);

	void getPlayerCard(Deck& deck);

	
	void updatePlayerCount(int val);
	std::vector<Card>& getPlayerHand(bool aceCheck);
	void getPlayerHand();
	int getPlayerCount();

	std::string getPlayerName();

	Card hitMovePlayer(Deck& deck);

	/*

	void doubleDownMove();
	void splitMove();*/
};
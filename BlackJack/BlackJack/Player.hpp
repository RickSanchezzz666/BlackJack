#pragma once
#include "Deck.hpp"
#include "Balance.hpp"
#include "Status.hpp"

#include <vector>
#include <string>

class Player : public Balance {
protected:
	Balance _balance;
	int _scoreCounter = 0;
	std::vector<Card> hand;

	std::string _name = "";

public:
	Status playerStatus;

	Player() : hand({}), playerStatus(Status::FINISHED) {};

	Player(Deck& deck, std::string& name);

	void setPlayerName(std::string& name);

	void getPlayerCard(Deck& deck);

	void getPlayerHand();
	int getPlayerCount();

	std::string getPlayerName();

	Card hitMovePlayer(Deck& deck);

	/*

	void doubleDownMove();
	void splitMove();*/
};
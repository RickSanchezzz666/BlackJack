#pragma once
#include "Deck.hpp"
#include "Balance.hpp"

#include <vector>
#include <string>

class Player : public Balance {
protected:
	Balance _balance;
	int _scoreCounter = 0;
	std::vector<Card> hand;

	std::string _name = "";

public:
	Player() {};

	Player(Deck& deck, std::string& name);

	void setPlayerName(std::string& name);

	void getCard(Deck& deck);

	void getHand();
	int getCount();

	/*
	void standMove();
	void hitMove();
	void doubleDownMove();
	void splitMove();*/
};
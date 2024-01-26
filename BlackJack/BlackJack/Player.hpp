#pragma once
#include "Deck.hpp"

#include <vector>

class Player {
protected:
	int _scoreCounter = 0;
	std::vector<Card> hand;

public:
	Player() {};

	Player(Deck& deck);

	void getCard(Deck& deck);

	/*
	void standMove();
	void hitMove();
	void doubleDownMove();
	void splitMove();*/

	void getHand();
	int getCount();
};
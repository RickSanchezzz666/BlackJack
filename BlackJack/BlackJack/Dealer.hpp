#pragma once
#include "Deck.hpp"

#include <vector>

class Dealer : public Deck {
protected:
	int _scoreCounter = 0;
	std::vector<Card> hand;

public:
	Dealer() {};

	Dealer(Deck& deck);

	void getCard(Deck& deck);
	/*
	void standMove();
	void hitMove();

	void resetDeck();
	void deckInitialize();*/

	void getHand();
	int getCount();
};
#pragma once
#include "Deck.hpp"

#include <vector>

class Game {
public: 
	static void updateHandCount(Card card, int& counter);

protected:
	virtual void getHand() = 0;
	virtual int getCount() = 0;

	virtual void getCard(Deck& deck) = 0;
	/*
	virtual void doubleDownMove();
	virtual void standMove();
	virtual void hitMove();
	virtual void splitMove();

	virtual void resetDeck();
	virtual void deckInitialize();*/
};
#pragma once
#include "Game.hpp"
#include "Deck.hpp"

#include <vector>

class Dealer : public Game, public Deck {
protected:
	int _scoreCounter = 0;
	std::vector<Card> hand;

public:
	Dealer(Deck& deck);

	void getCard(Deck& deck) override;
	/*
	void standMove() override;
	void hitMove() override;

	void resetDeck() override;
	void deckInitialize() override;*/

	void getHand() override;
	int getCount() override;
};
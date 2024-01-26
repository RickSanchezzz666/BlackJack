#pragma once
#include "Game.hpp"
#include "Deck.hpp"

#include <vector>

class Player : public Game, public Deck {
protected:
	int _scoreCounter = 0;
	std::vector<Card> hand;

public:
	Player(Deck& deck);

	void getCard(Deck& deck) override;
	/*

	void standMove() override;
	void hitMove() override;
	void doubleDownMove() override;
	void splitMove() override;*/

	void getHand() override;
	int getCount() override;
};
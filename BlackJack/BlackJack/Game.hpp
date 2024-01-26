#pragma once
#include "Deck.hpp"
#include "Dealer.hpp"
#include "Player.hpp"

class Game : public Dealer, public Player {
protected:
	Deck __deck;
	Dealer __dealer;

public:
	Game();

	static void updateHandCount(Card card, int& counter);
};
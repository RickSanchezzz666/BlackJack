#pragma once
#include "Deck.hpp"
#include "Dealer.hpp"
#include "Player.hpp"

#include <string>

class Game : public Dealer, public Player {
protected:
	Deck __deck;
	Dealer __dealer;

public:
	Game() {};

	Game(std::string name);

	static void updateHandCount(Card card, int& counter);
};
#pragma once
#include "Game.hpp"

#include <string>

class BlackJack : protected Game {
protected:
	bool _session = false;
	Game _game;
	std::string _name = "";

public:
	BlackJack();

	Balance balance;

	void startBlackJackGame();
};
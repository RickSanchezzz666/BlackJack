#pragma once
#include "Game.hpp"

#include <string>

class BlackJack : public Game {
protected:
	bool _session = false;
	Game _game;
	Balance _balance;
	std::string _name = "";

public:
	BlackJack();

	void startBlackJackGame();
};
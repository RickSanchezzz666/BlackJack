#pragma once
#include "Game.hpp"


class BlackJack : public Game {
protected:
	bool _session = false;
	Game _game;
public:
	BlackJack();

	int getBalance();

	void startBlackJackGame();
};
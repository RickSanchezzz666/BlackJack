#pragma once
#include "Game.hpp"


class BlackJack : public Game {
public:
	BlackJack();

	int getBalance();

	void prepareGame();

	void createGame(std::string& name);
};
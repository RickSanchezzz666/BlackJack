#include "BlackJack.hpp"

#include <iostream>
#include <string>

BlackJack::BlackJack() : _session(false) {
	std::cout << "Welcome to game BlackJack!\nEnter your name please: ";
	std::getline(std::cin, _name);
	startBlackJackGame();
}

void BlackJack::startBlackJackGame() {
	Game game;
	_game = game;
	prepareGame(game, _session, balance, _name);
}

#include "BlackJack.hpp"

#include <iostream>
#include <string>

BlackJack::BlackJack() : _session(false) {
	std::cout << "Welcome to game BlackJack!\nEnter your name please: ";
	std::getline(std::cin, _name);
	std::cout << "\nEnter balance that you want to have: ";
	int balanceNum;
	std::cin >> balanceNum;
	balance = Balance(balanceNum);
	startBlackJackGame();
}

void BlackJack::startBlackJackGame() {
	Game game;
	_game = game;
	prepareGame(game, _session, balance, _name);
}

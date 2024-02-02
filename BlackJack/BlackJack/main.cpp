#include "BlackJack.hpp"

#include <iostream>

int main() {
	BlackJack game;
	bool session = true;
	while (session) {
		std::cout << "\nChoose what you gonna do next:\n1. Start new game.\n2. Exit the programm\nEnter num: ";
		short action;
		std::cin >> action;
		switch (action)
		{
		case 1:
			game.startBlackJackGame();
			break;
		case 2:
			session = false;
			std::cout << "\nShutting down the program!\n";
			break;
		default:
			std::cout << "\nWrong action.Try again!\n";
			break;
		}
	}
	return 0;
}
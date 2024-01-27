#include "BlackJack.hpp"

#include <iostream>
#include <string>

BlackJack::BlackJack() : _session(false) {
	startBlackJackGame();
}

int BlackJack::getBalance() {
	return Balance::getBalance();
}

void BlackJack::startBlackJackGame() {
	prepareGame(_game, _session);
}

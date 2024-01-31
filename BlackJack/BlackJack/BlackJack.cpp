#include "BlackJack.hpp"

#include <iostream>
#include <string>

BlackJack::BlackJack() : _session(false) {
	startBlackJackGame();
}

void BlackJack::startBlackJackGame() {
	prepareGame(_game, _session);
}

#include "Game.hpp"
#include "Deck.hpp"
#include "Dealer.hpp"
#include "Player.hpp"

#include <string>

Game::Game(std::string name) {
	if (!name.empty()) {
		__deck = Deck();
		__dealer = Dealer(__deck);
		Player player(__deck, name);
	}
}

void Game::updateHandCount(Card card, int& counter) {
	counter += card.value;
}

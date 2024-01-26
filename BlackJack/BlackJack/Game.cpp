#include "Game.hpp"
#include "Deck.hpp"
#include "Dealer.hpp"
#include "Player.hpp"

Game::Game() {
	__deck = Deck();
	__dealer = Dealer(__deck);
	Player player(__deck);
}

void Game::updateHandCount(Card card, int& counter) {
	counter += card.value;
}

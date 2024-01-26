#include "Game.hpp"

void Game::updateHandCount(Card card, int& counter) {
	counter += card.value;
}

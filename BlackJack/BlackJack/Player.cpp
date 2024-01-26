#include "Player.hpp"
#include "Deck.hpp"

#include <iostream>

void Player::getHand() {
	std::cout << "Player's hand:\n";
	for (auto card : hand) {
		std::cout << "Card: " << card.name << " of " << card.suit << ". Cost: " << card.value << std::endl;
	}
}

int Player::getCount() {
	std::cout << "Player's count: " << _scoreCounter << std::endl;
	return _scoreCounter;
}

Player::Player(Deck& deck) {
	getCard(deck);
	getCard(deck);
	getHand();
	getCount();
}

void Player::getCard(Deck& deck) {
	hand.push_back(__getCardFromDeck(deck, _scoreCounter));
}

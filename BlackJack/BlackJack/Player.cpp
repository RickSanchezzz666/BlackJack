#include "Player.hpp"
#include "Deck.hpp"

#include <iostream>
#include <string>

void Player::getHand() {
	std::cout << "\nPlayer: '" << _name << "' hand:\n";
	for (auto card : hand) {
		std::cout << "Card: " << card.name << " of " << card.suit << ". Cost: " << card.value << std::endl;
	}
}

int Player::getCount() {
	std::cout << "Player: '" << _name << "' count: " << _scoreCounter << std::endl;
	return _scoreCounter;
}

Player::Player(Deck& deck, std::string& name) {
	setPlayerName(name);
	getCard(deck);
	getCard(deck);
	getHand();
	getCount();
}

void Player::setPlayerName(std::string& name) {
	_name = name;
}

void Player::getCard(Deck& deck) {
	hand.push_back(Deck::__getCardFromDeck(deck, _scoreCounter));
}

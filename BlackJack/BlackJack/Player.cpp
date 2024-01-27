#include "Player.hpp"
#include "Deck.hpp"

#include <iostream>
#include <string>

void Player::getPlayerHand() {
	std::cout << "\nPlayer: '" << _name << "' hand:\n";
	for (auto card : hand) {
		std::cout << "Card: " << card.name << " of " << card.suit << ". Cost: " << card.value << std::endl;
	}
}

int Player::getPlayerCount() {
	return _scoreCounter;
}

Card Player::hitMovePlayer(Deck &deck) {
	getPlayerCard(deck);
	return hand[hand.size() - 1];
}

std::string Player::getPlayerName() {
	return _name;
}

Player::Player(Deck& deck, std::string& name) {
	setPlayerName(name);
	getPlayerCard(deck);
	getPlayerCard(deck);
	getPlayerHand();
	std::cout << "Player: '" << _name << "' count: " << getPlayerCount() << std::endl;
}

void Player::setPlayerName(std::string& name) {
	_name = name;
}

void Player::getPlayerCard(Deck& deck) {
	hand.push_back(Deck::__getCardFromDeck(deck, _scoreCounter));
}

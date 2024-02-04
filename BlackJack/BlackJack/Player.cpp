#include "Player.hpp"
#include "Deck.hpp"
#include "Game.hpp"

#include <iostream>
#include <string>
#include <vector>

void Player::getPlayerHand() {
	std::cout << "\nPlayer: '" << _name << "' hand:\n";
	for (auto card : hand) {
		std::cout << "Card: " << card.name << " of " << card.suit << ". Cost: " << card.value << std::endl;
	}
}

void Player::getPlayerAddHand() {
	std::cout << "\nPlayer: '" << _name << "' additional hand:\n";
	for (auto card : addHand) {
		std::cout << "Card: " << card.name << " of " << card.suit << ". Cost: " << card.value << std::endl;
	}
}
void Player::updatePlayerCount(int val) {
	Game::updateHandCount(val, _scoreCounter);
}

void Player::updatePlayerCount(int val, bool split) {
	if (val < 0) {
		Game::updateHandCount(val, _scoreCounter, true);
	}
	else {
		Game::updateHandCount(val, _addScoreCounter, true);
	}
}

std::vector<Card>& Player::getPlayerHand(bool aceCheck) {
	return hand;
}

std::vector<Card>& Player::getPlayerHand(bool aceCheck, bool split) {
	return addHand;
}

int Player::getPlayerCount() {
	return _scoreCounter;
}

int Player::getPlayerCount(bool split) {
	return _addScoreCounter;
}

Card Player::hitMovePlayer(Deck &deck) {
	getPlayerCard(deck);
	return hand[hand.size() - 1];
}

Card Player::hitMovePlayer(Deck& deck, bool split) {
	getPlayerCard(deck, split);
	return addHand[addHand.size() - 1];
}

std::string Player::getPlayerName() {
	return _name;
}

void Player::splitMove() {
	if (addHand.empty()) {
		int val = hand[1].value;
		addHand.push_back(hand[1]);
		hand.pop_back();
		updatePlayerCount(-val, true);
		updatePlayerCount(val, true);
	}
}

void Player::__updateStake(int stake) {
	playerStake = stake;
}

void Player::__makeStake(Balance& _balance, int stake) {
	__updateStake(stake);
	updateBalance(_balance, -stake);
}

Player::Player(Deck& deck, std::string& name, Balance& _balance, int stake) {
	setPlayerName(name);
	__makeStake(_balance, stake);
	getPlayerCard(deck);
	getPlayerCard(deck);
	getPlayerHand();
	std::cout << "Player: '" << _name << "' count: " << getPlayerCount() << "\n\n";
}

void Player::setPlayerName(std::string& name) {
	_name = name;
}

void Player::getPlayerCard(Deck& deck) {
	hand.push_back(Deck::__getCardFromDeck(deck, _scoreCounter));
}

void Player::getPlayerCard(Deck& deck, bool split) {
	addHand.push_back(Deck::__getCardFromDeck(deck, _addScoreCounter));
}

int Player::getHandSize() {
	return hand.size();
}

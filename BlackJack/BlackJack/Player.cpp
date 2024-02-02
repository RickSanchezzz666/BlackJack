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

void Player::updatePlayerCount(int val) {
	Game::updateHandCount(val, _scoreCounter);
}

std::vector<Card>& Player::getPlayerHand(bool aceCheck) {
	return hand;
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

void Player::__updateStake(int stake) {
	playerStake = stake;
}

void Player::__makeStake(Balance& _balance) {
	short stake;
	std::cout << "\nEnter your stake: ";
	try { std::cin >> stake; }
	catch (const std::exception&) {
		std::cerr << "\nWrong type of data! Try again!";
		return __makeStake(_balance);
	}
	if (stake <= 0) {
		std::cerr << "\nStake must be above 0! Try again!";
		return __makeStake(_balance);
	}
	if (stake > getBalance(_balance)) {
		std::cerr << "\nYou dont have enough money to make a stake! Try again!";
		return __makeStake(_balance);
	}
	__updateStake(stake);
	updateBalance(_balance, -stake);
}

Player::Player(Deck& deck, std::string& name, Balance& _balance) {
	setPlayerName(name);
	__makeStake(_balance);
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

#include "Dealer.hpp"
#include "Game.hpp"

#include <iostream>
#include <vector>

void Dealer::getDealerHand() {
	std::cout << "\nDealer's hand:\n";
	for (auto card : hand) {
		std::cout << "Card: " << card.name << " of " << card.suit << ". Cost: " << card.value << std::endl;
	}
}

void Dealer::getDealerInitialHand() {
	std::cout << "\nDealer's hand:\n";
	auto card = hand[0];
	std::cout << "Card: " << card.name << " of " << card.suit << ". Cost: " << card.value << std::endl;
	std::cout << "Card: Hidden. Cost: X" << std::endl;
}

void Dealer::updateDealerCount(int val) {
	Game::updateHandCount(val, _scoreCounter);
}

std::vector<Card>& Dealer::getDealerHand(bool aceCheck) {
	return hand;
}

int Dealer::getDealerCount() {
	return _scoreCounter;
}

int Dealer::getDealerInitialCount() {
	auto card = hand[0];
	return card.value;
}

Dealer::Dealer(Deck& deck){
	getDealerCard(deck);
	getDealerInitialHand();
	std::cout << "Dealer's count: " << getDealerInitialCount() << std::endl;
}

void Dealer::getDealerCard(Deck& deck) {
	hand.push_back(__getCardFromDeck(deck, _scoreCounter));
}

Card Dealer::hitMoveDealer(Deck& deck) {
	getDealerCard(deck);
	return hand[hand.size() - 1];
}

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

void Dealer::updateDealerCount(int val) {
	Game::updateHandCount(val, _scoreCounter);
}

std::vector<Card> Dealer::getDealerHand(bool aceCheck) {
	return hand;
}

int Dealer::getDealerCount() {
	return _scoreCounter;
}

Dealer::Dealer(Deck& deck){
	getDealerCard(deck);
	getDealerCard(deck);
	getDealerHand();
	std::cout << "Dealer's count: " << getDealerCount() << std::endl;
}

void Dealer::getDealerCard(Deck& deck) {
	hand.push_back(__getCardFromDeck(deck, _scoreCounter));
}

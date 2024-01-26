#include "Dealer.hpp"

#include <iostream>

void Dealer::getHand() {
	std::cout << "Dealer's hand:\n";
	for (auto card : hand) {
		std::cout << "Card: " << card.name << " of " << card.suit << ". Cost: " << card.value << std::endl;
	}
}

int Dealer::getCount() {
	std::cout << "Dealer's count: " << _scoreCounter << std::endl;
	return _scoreCounter;
}

Dealer::Dealer(Deck& deck){
	getCard(deck);
	getCard(deck);
	getHand();
	getCount();
}

void Dealer::getCard(Deck& deck) {
	hand.push_back(__getCardFromDeck(deck, _scoreCounter));
}

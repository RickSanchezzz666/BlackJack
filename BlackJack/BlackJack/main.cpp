#include "Deck.hpp"
#include "Dealer.hpp"
#include "Player.hpp"

#include <iostream>

int main() {
	Deck deck;
	Dealer dealer(deck);
	Player player(deck);
	
	return 0;
}
#pragma once

#include <string>
#include <vector>

struct Card {
	std::string suit;
	std::string name;
	std::string shortName;
	short value;
	short addValue = 0;
	
	Card() : value(0), addValue(0) {}

	Card(std::string s, std::string n, std::string shortN, short val, short add = 0) 
		: suit(s), name(n), shortName(shortN), value(val), addValue(add) {}
};

class Deck {
protected:
	std::vector<Card> __deck;

	std::vector<Card> __initializeDeck();
	void __resetDeck();

public:
	Deck();

	static Card __getCardFromDeck(Deck& deck, int& counter);
};
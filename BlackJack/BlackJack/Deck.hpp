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
private:
	std::vector<Card> __deck;
public:
	Deck();
};
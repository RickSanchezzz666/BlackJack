#include "Deck.hpp"
#include "jsonRead.hpp"

#include "nlohmann/json.hpp"
#include <string>
#include <exception>
#include <iostream>

Deck::Deck() {
	try {
		nlohmann::json info = readJson("info.json");
		for (std::string x : info["deck"]["cards_suits"]) {
			for (auto card : info["deck"]["cards"]) {
				std::string name = card[0];
				std::string shortN = card[1];
				short val = card[2];
				short addVal = card[3];
				Card card(x, name, shortN, val);
				card.addValue = addVal;
				
				__deck.push_back(card);
			}
		}
	}
	catch (std::string &err) {
		std::cerr << "Error! JSON file is not opened!: " << err << std::endl;
	}
	catch (std::exception& err) {
		std::cerr << "Error occured while opening JSON file!: " << err.what() << std::endl;
	}
}
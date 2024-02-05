#include "Deck.hpp"
#include "jsonRead.hpp"
#include "Game.hpp"

#include "nlohmann/json.hpp"
#include <string>
#include <exception>
#include <iostream>
#include <random>

Deck::Deck() {
	__deck = __initializeDeck();
}

std::vector<Card> Deck::__initializeDeck() {
	try {
		nlohmann::json info = readJson("info.json");
		std::vector<Card> __deck;
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
		return __deck;
	}
	catch (std::string& err) {
		std::cerr << "Error! JSON file is not opened!: " << err << std::endl;
		return {};
	}
	catch (std::exception& err) {
		std::cerr << "Error occured while opening JSON file!: " << err.what() << std::endl;
		return {};
	}
}

void Deck::__resetDeck() {
	__deck.clear();
	std::cout << "Deck succesfully reseted!\n";
}

Card Deck::__getCardFromDeck(Deck& deck, int &counter) {
	try {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<size_t> dist(0, deck.__deck.size() - 1);
		size_t randomIndex = dist(gen) < deck.__deck.size() ? dist(gen) : throw std::out_of_range("Invalid index to get!");
		Card card = deck.__deck[randomIndex];
		deck.__deck.erase(deck.__deck.begin() + randomIndex);
		Game::updateHandCount(card, counter);
		return card;
	}
	catch (std::out_of_range& err) {
		std::cerr << "Invalid index was generated!" << err.what() << "Try again!\n";
		return __getCardFromDeck(deck, counter);
	}
}

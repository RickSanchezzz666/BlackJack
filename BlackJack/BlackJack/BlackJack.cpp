#include "BlackJack.hpp"

#include <iostream>
#include <string>

BlackJack::BlackJack() {
	prepareGame();
}

int BlackJack::getBalance() {
	return Balance::getBalance();
}

void BlackJack::prepareGame() {
	using namespace std;
	cout << "Welcome to game BlackJack!\nEnter your name please: ";
	string name = "";
	cin >> name;
	cout << "Hi " << name << ", now we are gonna start the first game!\n";
	cout << "Your initial balance is: " << getBalance() << std::endl;
	createGame(name);
}

void BlackJack::createGame(std::string& name) {
	Game game(name);
}

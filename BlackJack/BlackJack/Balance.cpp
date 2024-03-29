#include "Balance.hpp"

#include <iostream>

void Balance::resetBalance(Balance& balance) {
	balance.__balance = 0;
}

const int Balance::getBalance(Balance& balance) {
	return balance.__balance;
}

bool Balance::checkBalance(Balance& balance) {
	return balance.__balance > 0 ? true : false;
}

bool Balance::checkBalance(Balance& balance, int stake) {
	return balance.__balance - stake >= 0 ? true : false;
}


void Balance::updateBalance(Balance& balance, int value) {
	balance.__balance += value;
	if (!checkBalance(balance)) std::cerr << "\nPlayer's balance is below 0!\n";
}
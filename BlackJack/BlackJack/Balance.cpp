#include "Balance.hpp"

Balance::Balance() : __balance(100) {}

void Balance::resetBalance() {
	__balance = 0;
}

const int Balance::getBalance() {
	return __balance;
}

bool Balance::checkBalance() {
	return __balance > 0 ? true : false;
}

void Balance::updateBalance(int value) {
	__balance += value;
	if (!checkBalance()) throw("Balance is below 0!");
}
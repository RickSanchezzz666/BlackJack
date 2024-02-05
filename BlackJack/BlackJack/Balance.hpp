#pragma once

class Balance {
private:
	int __balance = 0;
public:
	Balance() {};
	Balance(int num) : __balance(num) {}

	void resetBalance(Balance& balance);
	const int getBalance(Balance& balance);
	void updateBalance(Balance& balance, int value);
	bool checkBalance(Balance& balance);

	bool checkBalance(Balance& balance, int stake);
};
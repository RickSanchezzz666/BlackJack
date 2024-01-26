#pragma once

class Balance {
private:
	int __balance = 0;
public:
	Balance();

	void resetBalance();
	const int getBalance();
	void updateBalance(int value);
	bool checkBalance();
};
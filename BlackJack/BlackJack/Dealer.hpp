#pragma once
#include "Deck.hpp"
#include "Status.hpp"

#include <vector>

class Dealer : public Deck {
protected:
	int _scoreCounter = 0;
	std::vector<Card> hand;

public:
	Status dealerStatus;

	Dealer() : hand({}), dealerStatus(Status::FINISHED) {};

	Dealer(Deck& deck);

	void getDealerCard(Deck& deck);
	Card hitMoveDealer(Deck& deck);


	void getDealerInitialHand();
	int getDealerInitialCount();

	void getDealerHand();
	int getDealerCount();

	std::vector<Card>& getDealerHand(bool aceCheck);

	void updateDealerCount(int val);
};
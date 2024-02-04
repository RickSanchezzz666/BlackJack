#pragma once

enum class Status {
	PROGRESS,
	PLAYER_WIN,
	DEALER_WIN,
	BLACKJACK,
	BUST,
	FINISHED
};

enum class SplitStatus {
	PROGRESS,
	FIRST_WIN,
	FIRST_BUST,
	SECOND_WIN,
	SECOND_BUST
};
#pragma once

enum class Actions {
	HIT,
	STAND,
	DOUBLE_DOWN,
	SPLIT
};

Actions getActionType(short int num);
#pragma once

enum class Actions {
	HIT,
	STAND,
	DOUBLE_DOWN,
	SPLIT
};


Actions getActionType(int num);


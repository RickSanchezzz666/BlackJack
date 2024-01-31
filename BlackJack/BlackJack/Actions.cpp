#include "Actions.hpp"

Actions getActionType(short int num) {
	switch (num)
	{
	case 1:
		return Actions::HIT;
	case 2:
		return Actions::STAND;
	case 3:
		return Actions::DOUBLE_DOWN;
	case 4:
		return Actions::SPLIT;
	}
}
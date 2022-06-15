#pragma once


int64_t func_largestthrow(std::vector<Diceset> dicesets, int64_t vectorsize) 
{
	int64_t result = 0;
	for (int64_t i = 0; i < vectorsize; i++) {
		if (dicesets[i].plusorminus == 1) {
			result += dicesets[i].amount * dicesets[i].alleyes[dicesets[i].sides - 1];
		}
		else {
			result -= dicesets[i].amount * dicesets[i].alleyes[dicesets[i].sides - 1];
		}
	}
	return result;
}
#pragma once
#include <vector>
#include <cmath>


int64_t func_maximumpossibilities(std::vector<Diceset> dicesets, int64_t size) {

	// Set integer equal 1 to multiply it with all other possibilities
	int64_t maximumpossibilities = 1;

	// Raise all sides to the power of the amount of dice thrown and multiply them to get the maximumpossibilities
	for (int64_t i = 0; i < size; i++) {
		maximumpossibilities *= static_cast<int64_t>(std::pow(dicesets[i].sides, dicesets[i].amount));
	}

	return maximumpossibilities;
}
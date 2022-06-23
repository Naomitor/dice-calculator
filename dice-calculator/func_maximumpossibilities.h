#pragma once


int64_t func_maximumpossibilities(std::vector<Diceset> dicesets)
{
	// Set integer equal 1 to multiply it with all other possibilities
	int64_t maximumpossibilities = 1;
	int64_t vectorsize = dicesets.size();

	// Raise all sides to the power of the amount of dice thrown and multiply them to get the maximumpossibilities
	for (int64_t i = 0; i < vectorsize; i++) {
		maximumpossibilities *= static_cast<int64_t>(std::pow(dicesets[i].sides, dicesets[i].amount));
	}
	return maximumpossibilities;
}
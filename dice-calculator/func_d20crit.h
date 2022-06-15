#pragma once

double func_d20crit(std::vector<Diceset> dicesets, int64_t threshold) 
{
	// Highest z of xdy =  1-((1-(y-z+1)/y))^x)
	double result = 0;

	result = static_cast<double>(dicesets[0].sides - threshold + 1);
	result /= dicesets[0].sides;
	result = 1 - result;
	result = std::pow(result, dicesets[0].amount);
	result = 1 - result;
	result = result * 100.0;

	return result;
}
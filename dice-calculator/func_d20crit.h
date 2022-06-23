#pragma once

double func_d20crit(std::vector<Diceset> dicesets, int64_t threshold) 
{
	// Highest z of xdy =  1-((1-(y-z+1)/y))^x)
	double result = 0.0;

	result = (1 - (std::pow(1 - ((static_cast<double>(dicesets[0].sides - threshold + 1)) / dicesets[0].sides), dicesets[0].amount))) * 100.0;

	return result;
}
#pragma once


double func_meanthrow(std::vector<Diceset> dicesets, int64_t size)
{
	double meanthrow = 0;
	for (int64_t i = 0; i < size; i++) {
		double alleyesresult = 0;
		int64_t alleyessize = dicesets[i].alleyes.size();
		for (int64_t j = 0; j < alleyessize; j++) {
			alleyesresult += dicesets[i].alleyes[j];
		}
		alleyesresult = alleyesresult * dicesets[i].amount;
		meanthrow += alleyesresult / dicesets[i].alleyes.size();
	}
	return meanthrow;
}

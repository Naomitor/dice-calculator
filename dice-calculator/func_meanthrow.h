#pragma once


double func_meanthrow(std::vector<Diceset> dicesets)
{
	double meanthrow = 0;
	int64_t vectorsize = dicesets.size();
	for (int64_t i = 0; i < vectorsize; i++) {
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

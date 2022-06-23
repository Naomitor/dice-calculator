#pragma once

std::vector<Superdieresult> func_stevieoreaditsuperdie(sortedinput varsortedinput)
{
	std::vector<Superdieresult> superdieresults;
	superdieresults.reserve(func_largestthrow(varsortedinput.dicesets) - func_smallestthrow(varsortedinput.dicesets));

	for (int64_t i = 0, dicesetssize = varsortedinput.dicesets.size(); i < dicesetssize; i++)
	{
		for (int64_t j = 0; j < varsortedinput.dicesets[i].amount; j++)
		{
			for (int64_t k = 0; k < varsortedinput.dicesets[i].sides; k++)
			{
				int64_t superdieresultssize = superdieresults.size();
				int64_t comparison = 0;
				if (superdieresultssize == 0) {
					comparison = varsortedinput.dicesets[i].sides;
				}
				else {
					comparison = superdieresultssize;
				}

				for (int64_t l = 0; l < comparison; l++)
				{
					int64_t superdieresult = superdieresults[l].number + varsortedinput.dicesets[i].alleyes[k];
					std::_Vector_iterator it = find_if(superdieresults.begin(), superdieresults.end(), [&superdieresult](const Superdieresult& obj) {return obj.number == superdieresult; });
					if (it != superdieresults.end())
					{
						int64_t index = std::distance(superdieresults.begin(), it);
						superdieresults.at(index).amount ++;
					}
					else
					{
						superdieresults.push_back(Superdieresult(1, superdieresult));
					}
				}
			}
		}
	}
	superdieresults.resize(superdieresults.size());
	return superdieresults;
}
#pragma once


// Class Die that holds the amount of sides the die has a vector of all eyes on each side and of it is to be added or subtracted

class Die{
	public:
		bool plusorminus;
		int64_t sides{};
		std::vector<int64_t> alleyes;
};


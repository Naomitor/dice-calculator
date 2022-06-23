#pragma once
#include "class_Die.h"


// Class Diewithside inherits from class Die and adds the current side for iteration purposes 

class Diewithside: public Die 
{
	public:
		int64_t dieside{};
};


#pragma once
#include "class_Diceset.h"

// The structure sortedinput is used to pass the getdicesets return values to the other functions

struct sortedinput 
{
    int64_t addsubtract{};
    std::vector<Diceset> dicesets;
} 

typedef sortedinput;
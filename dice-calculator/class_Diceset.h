#pragma once
#include "class_Die.h"

// Class for Dicesets that inherits from Die and adds the amount of dice thrown

class Diceset : public Die {
    public:
        int64_t amount{};
};


#pragma once
#include <vector>
#include "Diceset.h"
#include <iostream>
#include <string>

//
std::string userinput;

void func_getdicesets() {
	// Display message for user
	std::cout << "Please input your dice set" << std::endl;
	// Get the user input it should look like this: 2d6+1d{2,3,4,4}-5
	// 2d6 being 2 dice of standard layout with six sides showing the eyes 1,2,3,4,5,6
	// 1d{2,3,4,4} being a special dice that has 4 sides showing the eyes 2,3,4,4
	// +/- operator for spacing and simpel number addition/subtraciton

	std::cin >> userinput;

	// Search for characters that are not supposed to be in the input and count the number of d´s
	int64_t foundwronginputindex = userinput.find_first_not_of("1234567890d,+-{}");
	int64_t dcount = std::count(userinput.begin(), userinput.end(), 'd');

	// If there are wrong characters or no d´s output help for the user
	if (foundwronginputindex != -1) {
		std::cout << "Looks like there are characters in the input that I did not recognize";
	}
	else if (dcount == 0) {
		std::cout << "You forgot the d ;)";
	}
	// Else start the process
	else {
		
		std::vector<Dicesets> dicesets;
		dicesets.reserve(dcount);

		// For the amount of d´s (dice sets) found in the input, break them up into diceset objects
		for (int i = 0; i < dcount; i++) {
			// Find the next d and braket
			int64_t nextdindex = userinput.find("d");
			int64_t braketindex = userinput.find("{");
			
			// If a braket comes after the next d, it signals a special dice and it will be handeld by this  
			if (braketindex - nextdindex == 1) {
				// Fill the dice amount of the set into amount and remove the numbers and d from the string
				int dicethrown = std::stoi(userinput.substr(0, nextdindex));
				userinput = userinput.erase(0, nextdindex + 1);

				// Set the amount of sides a single die has and filter the eyes on each side into a vector
				int64_t operatorindex = userinput.find_first_of("+-");
				std::string specialdiesides;
				std::vector<int> eyes;
				// If no +/- has been found length is the whole string, else the counts up to the index of the operator
				if (operatorindex >= 1) {
					specialdiesides = userinput.substr(1, operatorindex - 2);
				}
				else {
					specialdiesides = userinput.substr(1, userinput.length() - 2);
				}
				int diesides = lround(specialdiesides.length() / 2);
				eyes.reserve(diesides);
				for (i = 0; i <= diesides * 2; i += 2) {
					eyes.push_back(int(std::stoi(specialdiesides.substr(i, 1))));
				}
				dicesets.push_back(Dicesets(diesides, eyes, dicethrown));
			}
		}
			//filter normal dice and create a vector for it


		//2d{2,4,6}

	}
}
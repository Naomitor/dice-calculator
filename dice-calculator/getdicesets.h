#pragma once
#include <vector>
#include "Diceset.h"
#include <iostream>
#include <string>

// Initiate variabls
std::string userinput;

//
void func_getdicesets() {
	// Get the user input it should look like this: 2d6+1d{2,3,4,4}-5
	// 2d6 being 2 dice of standard layout with six sides showing the eyes 1,2,3,4,5,6
	// 1d{2,3,4,4} being a special dice that has 4 sides showing the eyes 2,3,4,4
	// +/- operator for spacing and simpel number addition/subtraciton
	std::cin >> userinput;

	// Search for characters that are not supposed to be in the input and count the number of d´s
	int foundindex = userinput.find_first_not_of("1234567890d,+-{}");
	int dcount = std::count(userinput.begin(), userinput.end(), 'd');

	// If there are wrong characters or no d´s output help for the user
	if (foundindex != -1) {
		std::cout << "Looks like there are characters in the input that I did not recognize";
	}
	else if (dcount == 0) {
		std::cout << "You forgot the d ;)";
	}
	// Else start the process
	else {
		int braketindex = userinput.find("{");
		int operatorindex = userinput.find_first_of("+-");
		int dindex = userinput.find("d");

		std::vector<Dicesets> dicesets;
		dicesets.reserve(dcount);

		// For the amount of d´s (dice sets) found in the input, break them up into diceset objects
		for (int i = 0; i <= dcount; i++) {
			// If a braket comes after the next d, it signals a special dice and it will be handeld by this  
			if (braketindex - dindex == 1) {
				// Fill the dice amount of the set in
				int amount = std::stoi(userinput.substr(0, dindex));
				// Set the amount of dice sides
				
				// Filter the dice sides into the vector
				for (int i = 0; ) {

				}
			}
		}

			//filter special dice

			//filter normal dice and create a vector for it


		std::cout << "That worked";

	}
}
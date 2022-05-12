#pragma once
#include <vector>
#include "Diceset.h"
#include <iostream>
#include <string>

void func_getdicesets() {

	// Display message for user
	std::cout << "Please input your dice set/sets and anthing you want to add or subtract" << std::endl;

	// Get the user input it should look like this: 2d6+1d{2,3,4,4}-5
	// 2d6 being 2 dice of standard layout with six sides showing the eyes 1,2,3,4,5,6
	// 1d{2,3,4,4} being a special dice that has 4 sides showing the eyes 2,3,4,4
	// +/- operator for number addition/subtraciton

	std::string userinput;
	std::cin >> userinput;

	// Set a plus infront of the string and a minus behind to get pointers for the first and last operation
	userinput = "+" + userinput + "-";

	// Search for characters that are not supposed to be in the input and count the number of d큦
	int64_t foundwronginputindex = userinput.find_first_not_of("1234567890d,+-{}");
	int64_t dcount = std::count(userinput.begin(), userinput.end(), 'd');

	// If there are wrong characters or no d큦, output help for the user
	if (foundwronginputindex != -1) {
		std::cout << "Looks like there are characters in the input that I did not recognize";
	}
	else if (dcount == 0) {
		std::cout << "You forgot the d ;)";
	}

	// Else start the process of filtering the string
	else {

		// Find the amount of +/- in the string
		int64_t plusminuscount = std::count(userinput.begin(), userinput.end(), '+');
		plusminuscount += std::count(userinput.begin(), userinput.end(), '-');

		// Initialize the vector for the class Diceset, dicesets and set the amount of d큦 as reserve
		std::vector<Diceset> dicesets;
		dicesets.reserve(dcount);

		// Declare addsubtract befor the loop because it needs to be returned with the dicesets vector
		int addsubtract = 0;

		// For the amount of d큦 (dice sets) found in the input, break them up into diceset objects
		for (int i = 0; i < plusminuscount - 1; i++) {

			// Set the bool to true if it is plus or false if it is minus
			bool plusminus;
			if (userinput[0] == '+') {
				plusminus = true;
			}
			else {
				plusminus = false;
			}
			userinput = userinput.erase(0, 1);

			// Find the next d, open braket and +/-
			int64_t nextdindex = userinput.find("d");
			int64_t braketindex = userinput.find("{");
			int64_t secondoperatorindex = userinput.find_first_of("+-");

			// If the next part of userinput is a addition or subtraction of a number filter it out of the string and add or subtract it to addsubtract.
			// After that remove the numbers out of the string.
			if (nextdindex == - 1 || nextdindex - secondoperatorindex >= 2) {
				if (plusminus) {
					addsubtract += std::stoi(userinput.substr(0, secondoperatorindex));
				}
				else {
					addsubtract -= std::stoi(userinput.substr(0, secondoperatorindex));
				}
				userinput = userinput.erase(0, secondoperatorindex);
			}

			// If a braket comes after the next d, it signals a special die and it will be handeld by this  
			else if (braketindex - nextdindex == 1) {

				// Fill the dice amount of the set into amount and remove the numbers and d from the string
				int dicethrown = std::stoi(userinput.substr(0, nextdindex));
				userinput = userinput.erase(0, nextdindex+1);

				// Define the vetor for the amount of eyes on each side, the string for the special die and find the second +/-
				std::vector<int> eyes;
				std::string specialdiesides;
				secondoperatorindex = secondoperatorindex - (nextdindex + 1);

				// Remove the brackets aroung the special die eyes, assign it to a new string and remove that part from input if there is no typo, if there is read ouput
				if (secondoperatorindex >= 3) {
					specialdiesides = userinput.substr(1, secondoperatorindex - 2);
					userinput = userinput.erase(1, secondoperatorindex);
				}
				else {
					std::cout << "Either you forgot a braket {} or there is no number in the brakets";
					break;
				}

				// The amount of sides a die has, is calculated by rounding the special die input and adding one
				int diesides = lround(specialdiesides.length() / 2) + 1;

				// This gets set as reserve for eyes vector
				eyes.reserve(diesides);

				// After which the eyes on each side of the die get filterd into the eyes vector
				for (i = 0; i < diesides * 2; i += 2) {
					eyes.push_back(int(std::stoi(specialdiesides.substr(i, 1))));
				}

				// The amount of dice thrown, die sides and the vector with all eyes on a die get pushed into the objects vector dicesets of class Diceset
				dicesets.push_back(Diceset{diesides, eyes, dicethrown, plusminus});
				
				//std::cout << dicesets[0].sides << std::endl << dicesets[0].alleyes[1] << std::endl << dicesets[0].amount << std::endl << dicesets[0].plusorminus << std::endl;
			}
		}
	}
}
//filter normal dice and create a vector for it
//2-5+6+2d{4,5}
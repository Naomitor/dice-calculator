#pragma once
#include "class_Diceset.h"
#include "struct_sortedinput.h"


// The function getdicesets sorts a user input into a vector of Dicesets and an interger to be added or subtracted and returns it in the structure Sortedinput

sortedinput func_getdicesets() 
{
	sortedinput output;

	// Display message for user
	std::cout << "Please input your dice set/sets and anthing you want to add or subtract" << std::endl;

	// Get the user input it should look like this: 2d6+1d{2,3,4,4}-5
	// 2d6 being 2 dice of standard layout with six sides showing the eyes 1,2,3,4,5,6
	// 1d{2,3,4,4} being a special dice that has 4 sides showing the eyes 2,3,4,4
	// +/- operator for number addition/subtraciton

	std::string userinput;
	std::cin >> userinput;

	// Search for characters that are not supposed to be in the input and count the number of d´s
	int64_t foundwronginputindex = userinput.find_first_not_of("1234567890d,+-{}");
	int64_t dcount = std::count(userinput.begin(), userinput.end(), 'd');


	// Initialize the vector for the class Diceset, dicesets and set the amount of d´s as reserve
	std::vector<Diceset> dicesets;
	dicesets.reserve(dcount);
	int64_t addsubtract = 0;
	bool error = false;

	// If there are wrong characters or no d´s, output help for the user, else start the process of filtering the string
	if (foundwronginputindex != -1) {
		std::cout << "Looks like there are characters in the input that I do not recognize";
		error = true;
	}
	else if (dcount == 0) {
		std::cout << "You forgot the d ;)";
		error = true;
	}
	else {

		// Set a plus infront of the string and a minus behind to get pointers for the first and last operation
		userinput = "+" + userinput + "-";

		// Find the amount of +/- in the string
		int64_t plusminuscount = std::count(userinput.begin(), userinput.end(), '+');
		plusminuscount += std::count(userinput.begin(), userinput.end(), '-');
		plusminuscount -= 1;

		// For the amount of +/- found in the input, sort the string into addsubtract or create Diceset objects
		for (int64_t i = 0; i < plusminuscount; i++) {

			// Set the bool to true if it is plus or false if it is minus
			bool plusminus;
			if (userinput[0] == '+') {
				plusminus = true;
			}
			else {
				plusminus = false;
			}
			// Remove the symbol from the string
			userinput = userinput.erase(0, 1);

			// Find the next d, open braket and +/-
			int64_t nextdindex = userinput.find("d");
			int64_t braketindex = userinput.find("{");
			int64_t secondoperatorindex = userinput.find_first_of("+-");

			// If the next part of userinput is a addition or subtraction of a number filter it out of the string and add or subtract it from addsubtract.
			// After that remove the numbers out of the string.
			if (nextdindex == -1 || nextdindex - secondoperatorindex >= 2) {
				if (plusminus) {
					addsubtract += std::stoi(userinput.substr(0, secondoperatorindex));
				}
				else {
					addsubtract -= std::stoi(userinput.substr(0, secondoperatorindex));
				}
				userinput = userinput.erase(0, secondoperatorindex);
			}

			// This either creates a special die out of a standart and processes it into a vector of objects or just does the later for special dice
			else {

				// Fill the dice amount of the set into amount and remove the numbers and d from the string
				int64_t dicethrown = std::stoi(userinput.substr(0, nextdindex));
				userinput = userinput.erase(0, nextdindex + 1);

				// Define the string for the special die and initialze diesides
				std::string specialdiesides;
				int64_t diesides = 0;


				// Else 
				if (braketindex - nextdindex == 1) {
					// Remove the brackets around the special die eyes, assign it to a new string and remove that part from userinput
					specialdiesides = userinput.substr(1, secondoperatorindex - nextdindex - 3);
					userinput = userinput.erase(0, secondoperatorindex - nextdindex - 1);
					specialdiesides = specialdiesides + ",";
					diesides = std::count(specialdiesides.begin(), specialdiesides.end(), ',');
				}
				else {
					// Create a special die out of a normal die, by starting at one and increasing to the number of sides, assign them to new string and remove sides from input
					diesides = static_cast<int64_t>(std::stoi(userinput.substr(0, secondoperatorindex - nextdindex - 1)));
					userinput = userinput.erase(0, secondoperatorindex - nextdindex - 1);
					for (int64_t i = 1; i <= diesides; i++) {
						specialdiesides.append(std::to_string(i) + ",");
					}
				}

				// Define the vetor for the amount of eyes on each side and set as reserve for it
				std::vector<int64_t> eyes;
				eyes.reserve(diesides);

				// After which the eyes on each side of the die get filterd into the eyes vector
				for (int64_t i = 0; i < diesides; i++) {
					int64_t commaindex = specialdiesides.find(",");
					eyes.push_back(int64_t(std::stoi(specialdiesides.substr(0, commaindex))));
					specialdiesides.erase(0, commaindex + 1);
				}

				// The amount of dice thrown, die sides and the vector with all eyes on a die get pushed into the objects vector dicesets of class Diceset
				dicesets.push_back(Diceset{plusminus, diesides, eyes, dicethrown});
			}
		}
	}
	// Fill the dicesets vector and addsubtract integer into the structure and return to caller
	output.addsubtract = addsubtract;
	output.dicesets = dicesets;
	return output;
}
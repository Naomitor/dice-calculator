#pragma once
#include <mutex>
#include <thread>
#include <algorithm>
#include "class_Diewithside.h"
#include "struct_Sortedinput.h"
#include "func_maximumpossibilities.h"

std::mutex superdielock;


//
void func_multicreator(std::vector<Diewithside> dicewithside, int64_t lastdieside, int64_t size, int64_t lastdiepossibilities, std::vector<int64_t> &superdie) {
	
	// Set the last die side to number of the thread
	dicewithside[size-1].dieside = lastdieside;
	//
	std::vector<int64_t> partsuperdie;
	partsuperdie.reserve(lastdiepossibilities);

	// Calculate all possible results of all dice thrown with the last one set
	for (int64_t i = 0; i < lastdiepossibilities; i++) {
		
		// Reset the result
		int64_t result = 0;
		for (int64_t j = 0; j < size; j++) {
			result += dicewithside[j].alleyes[dicewithside[j].dieside];
		}
		partsuperdie.push_back(result);

		//
		for (int64_t j = 0; j < size - 1; j++) {
			if (dicewithside[j].dieside == dicewithside[j].sides - 1) {
				dicewithside[j].dieside == 0;
			}
			else {
				dicewithside[j].dieside += 1;
				break;
			}
		}
	}

	superdielock.lock();
	for (int64_t i = 0; i < lastdiepossibilities; i++) {
		superdie.push_back(partsuperdie[i]);
	}
	superdielock.unlock();
}




// The function superdie creates an array that holds all possible outcomes of the dice thrown
std::vector<int64_t> func_superdie(sortedinput varsortedinput) {

	// Get the size of the diceset vector and create a new vector out of class Diewithside
	int64_t size = varsortedinput.dicesets.size();
	std::vector<Diewithside> dicewithside;

	// Initialize the integer amount and iterate through all the amounts of vector dicesets adding them together to set the vector dicewithside reserve
	int64_t amount = 0;
	for (int64_t i = 0; i < size; i++) {
		amount += varsortedinput.dicesets[i].amount;
	}
	dicewithside.reserve(amount);

	// Fill the new vector dicewithside with each single die and add the starting value of 0
	for (int64_t i = 0; i < size; i++) {
		for (int64_t j = 0; j < varsortedinput.dicesets[i].amount; j++) {
			dicewithside.push_back(Diewithside{varsortedinput.dicesets[i].plusorminus, varsortedinput.dicesets[i].sides, varsortedinput.dicesets[i].alleyes, 0});
		}
	}

	// Get the maximum possibilities and divide by sides of the last die to get the amount of iterations each thread has to run
	int64_t maximumpossibilities = func_maximumpossibilities(varsortedinput.dicesets, size);
	int64_t lastdiepossibilities = maximumpossibilities / dicewithside[amount-1].sides;

	// Multithread calculate all possibilities and save them in array
	std::vector<int64_t> superdie;
	superdie.reserve(maximumpossibilities);
	std::thread thread_superdiecreator;
	for (int64_t i = 0; i < dicewithside.back().sides; i++) {
		std::thread thread_superdiecreator(func_multicreator, dicewithside, i, amount, lastdiepossibilities, superdie);
	}
	thread_superdiecreator.join();

	return superdie;
}
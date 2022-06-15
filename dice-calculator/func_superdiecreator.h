#pragma once
#include "class_Diewithside.h"
#include "class_Superdieresult.h"

#include "func_maximumpossibilities.h"
#include "func_largestthrow.h"
#include "func_smallestthrow.h"

#include "struct_Sortedinput.h"


std::mutex superdielock;


void func_multicreator(std::vector<Diewithside> dicewithside, int64_t lastdieside, int64_t size, 
	int64_t lastdiepossibilities, int64_t numberofresults, std::vector<int64_t> &superdieamount, std::vector<int64_t> &superdienumber) 
{
	// Set the last die side to the number of the thread
	dicewithside[size-1].dieside = lastdieside;

	//
	std::vector<int64_t> partsuperdieamount, partsuperdienumber;
	partsuperdieamount.reserve(numberofresults);
	partsuperdienumber.reserve(numberofresults);

	// Calculate all possible results of all dice thrown with the last one set
	for (int64_t i = 0; i < lastdiepossibilities; i++) {
		
		// Reset the result, add all active sides together and push them into the vector partsuperdie
		int64_t result = 0;
		for (int64_t j = 0; j < size; j++) {
			result += dicewithside[j].alleyes[dicewithside[j].dieside];
		}

		auto it = find(partsuperdienumber.begin(), partsuperdienumber.end(), result);
		int64_t index = std::distance(partsuperdienumber.begin(), it);

		if (it != partsuperdienumber.end()) {
			partsuperdieamount.at(index) += 1;
		}
		else {
			partsuperdieamount.push_back(1);
			partsuperdienumber.push_back(result);
		}

		// Check if the last die side has been reached if this is the case reset the side else raise it by one and break
		for (int64_t j = 0; j < size - 1; j++) {
			if (dicewithside[j].dieside == dicewithside[j].sides - 1) {
				dicewithside[j].dieside = 0;
			}
			else {
				dicewithside[j].dieside += 1;
				break;
			}
		}
	}
	int64_t partsuperdienumbersize = partsuperdienumber.size();


	// Add each partsuperdie to the superdie
	superdielock.lock();

	for (int64_t i = 0; i < partsuperdienumbersize; i++) {

		auto it = find(superdienumber.begin(), superdienumber.end(), partsuperdienumber[i]);
		int64_t index = std::distance(superdienumber.begin(), it);

		if (it != superdienumber.end()) {
			superdieamount.at(index) += partsuperdieamount[i];
		}
		else {
			superdieamount.push_back(partsuperdieamount[i]);
			superdienumber.push_back(partsuperdienumber[i]);
		}
	}

	superdielock.unlock();
}

bool Comparenumbers(const Superdieresult& left, const Superdieresult& right) {
	return left.number < right.number;
}


// The function superdie creates a vector that holds all possible outcomes of the dice thrown
std::vector<Superdieresult> func_superdiecreator(sortedinput varsortedinput) 
{

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

	// Get the smallest and largest throw
	int64_t largestthrow = func_largestthrow(varsortedinput.dicesets, size);
	int64_t smallestthrow = func_smallestthrow(varsortedinput.dicesets, size);
	int64_t numberofresults = largestthrow - smallestthrow;

	// Multithread calculate all possibilities and save them in array
	std::vector<int64_t> superdieamount, superdienumber;
	superdieamount.reserve(numberofresults);
	superdienumber.reserve(numberofresults);
	std::vector<std::thread> thread_superdiecreator;
	

	for (int64_t i = 0; i < dicewithside.back().sides; i++) {
		thread_superdiecreator.emplace_back(func_multicreator, dicewithside, i, amount, lastdiepossibilities, numberofresults, 
			std::reference_wrapper(superdieamount), std::reference_wrapper(superdienumber));
	}

	for (auto& t : thread_superdiecreator) {
		t.join();
	}


	superdieamount.shrink_to_fit();
	superdienumber.shrink_to_fit();
	std::vector<Superdieresult> superdie;
	size = superdieamount.size();

	for (int64_t i = 0; i < size; i++) {
		superdie.push_back(Superdieresult(superdieamount[i], superdienumber[i]));
	}

	std::sort(superdie.begin(), superdie.end(), Comparenumbers);

	return superdie;
}
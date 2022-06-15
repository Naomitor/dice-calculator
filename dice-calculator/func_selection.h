#pragma once
#include "func_getdicesets.h"
#include "func_largestthrow.h"
#include "func_maximumpossibilities.h"
#include "func_smallestthrow.h"
#include "func_superdiecreator.h"
#include "func_meanthrow.h"
#include "func_d20crit.h"

using namespace std::chrono_literals;

// Largest throw
void largestthrow() 
{
	sortedinput diceinput = func_getdicesets();
	int64_t size = diceinput.dicesets.size();
	int64_t largestthrowresult = func_largestthrow(diceinput.dicesets, size);
	largestthrowresult += diceinput.addsubtract;
	std::cout << "The largest possible throw is: " << largestthrowresult << std::endl << std::endl;
	std::this_thread::sleep_for(2s);
}


// Smallest throw
void smallestthrow() 
{
	sortedinput diceinput = func_getdicesets();
	int64_t size = diceinput.dicesets.size();
	int64_t smallestthrowresult = func_smallestthrow(diceinput.dicesets, size);
	smallestthrowresult += diceinput.addsubtract;
	std::cout << "The smallest possible throw is: " << smallestthrowresult << std::endl << std::endl;
	std::this_thread::sleep_for(2s);
}


// Maximum possibilities outcomes
void maximumpossibilities() 
{
	sortedinput diceinput = func_getdicesets();
	int64_t size = diceinput.dicesets.size();
	int64_t maximumpossibilitiesresult = func_maximumpossibilities(diceinput.dicesets, size);
	maximumpossibilitiesresult += diceinput.addsubtract;
	std::cout << "There are: " << maximumpossibilitiesresult << " possibile outcomes from this throw" << std::endl << std::endl;
	std::this_thread::sleep_for(2s);
}


// Mean throw with adding dice together
void meanthrow()
{
	sortedinput diceinput = func_getdicesets();
	int64_t size = diceinput.dicesets.size();
	double meanthrowresult = func_meanthrow(diceinput.dicesets, size);
	meanthrowresult += diceinput.addsubtract;
	std::cout << "The mean throw is: " << meanthrowresult << std::endl << std::endl;
	std::this_thread::sleep_for(2s);
}


// Mean throw with taking the highest die


// D20 Crit with selection of dice thrown and crit start
void d20crit()
{
	std::cout << "Please input your amount of d20 and the crit threshold like this: 3d20+19" << std::endl;
	sortedinput diceinput = func_getdicesets();
	int64_t size = diceinput.dicesets.size();
	double d20critresult = func_d20crit(diceinput.dicesets, diceinput.addsubtract);
	std::cout << "The chance to crit is " << std::setprecision(3) << d20critresult << "%" << std::endl << std::endl;
	std::this_thread::sleep_for(2s);
}

// This is where the user decides what to do next
int64_t func_selection() 
{
	bool stop = true;

	// Output all options
	std::cout << "(1) Calculate the largest result" << std::endl << "(2) Calculate the smallest result"
		<< std::endl << "(3) Calculate the amount of possibilities" << std::endl << "(4) Calculate the mean throw while adding the dice together"
		<< std::endl << "(5) Calculate the mean throw while taking the highest die" << std::endl << "(6) Exit" << std::endl << "Please select what you want to do: ";

	std::string userselection;
	std::cin >> userselection;

	int64_t foundwronginputindex = userselection.find_first_not_of("123456");
	int64_t userselectioncount = userselection.length();

	if (foundwronginputindex != -1) {
		std::cout << "That input does not contain a valid number" << std::endl;
	}
	else if (userselectioncount >= 2) {
		std::cout << "That are to many numbers" << std::endl;
	}
	else {
		int64_t userselectionint;
		userselectionint = std::stoi(userselection);

		if (userselectionint == 1) {
			largestthrow();
		}
		else if (userselectionint == 2) {
			smallestthrow();
		}
		else if (userselectionint == 3) {
			maximumpossibilities();
		}
		else if (userselectionint == 4) {
			meanthrow();
		}
		else if (userselectionint == 5) {
			d20crit();
		}
		else if (userselectionint == 6) {
			stop = false;
			return stop;
		}
	}
	
	return stop;
}
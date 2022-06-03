// dice-calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "getdicesets.h"
#include "struct_sortedinput.h"


int main(){
    sortedinput input = getdicesets();
    }

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Ideas:
// For crit with possible adv/dis and/or elvenluck:
// Highest z of xdy =  ((y-z)/y)^x
// 
// Meanthrow
// (All eyes on die / sides on die) * diceset
//
// Chance to get equal and more:
// possibilities/maximum posibilities 
//
// Maximum possibilities:
// length of super die
//
// Super die:
// all possible dice throws in one array
//
// Chance to get equal for plotting graph:
// possibilities/maximum posibilities

// Websites
// https://www.w3schools.com/cpp/cpp_conditions.asp
// https://www.programiz.com/cpp-programming/vectors
// https://stackoverflow.com/questions/8011887/how-can-i-create-multiple-objects-with-for-loop-in-c
// https://www.geeksforgeeks.org/multithreading-in-cpp/
// https://www.gigacalculator.com/calculators/dice-probability-calculator.php#two-six-sided
// https://www.geeksforgeeks.org/how-to-return-multiple-values-from-a-function-in-c-or-cpp/
#include <iostream>
#include "func_getdicesets.h"
#include "struct_sortedinput.h"
#include "func_superdiecreator.h"
#include <chrono>


int main(){

    std::chrono::time_point<std::chrono::system_clock> start, end;

    // First select what the user wants to do

    // Call getdicesets to get the user input for all the actions
    sortedinput varsortedinput = func_getdicesets();

    start = std::chrono::system_clock::now();

    // Output user request
    std::vector<int64_t> superdie = func_superdiecreator(varsortedinput);

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << superdie.size() << std::endl << superdie[0] << std::endl << superdie[superdie.size() - 1] << std::endl << "elapsed time: " << elapsed_seconds.count() << std::endl;
}

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
// Chance to get equal for plotting graph:
// possibilities/maximum posibilities


// Ready:
//
// Maximum possibilities:
// length of super die OR dice sides ^ dice amount * each other dicesets
//
// Super die:
// all possible dice throws in one array


// Websites
// https://www.w3schools.com/cpp/cpp_conditions.asp
// https://www.programiz.com/cpp-programming/vectors
// https://stackoverflow.com/questions/8011887/how-can-i-create-multiple-objects-with-for-loop-in-c
// https://www.geeksforgeeks.org/multithreading-in-cpp/
// https://www.gigacalculator.com/calculators/dice-probability-calculator.php#two-six-sided
// https://www.geeksforgeeks.org/how-to-return-multiple-values-from-a-function-in-c-or-cpp/
#include <iostream>
#include <mutex>
#include <algorithm>

#include "func_selection.h"



int main(){

    bool repeat = true;
    while (repeat == true) {
        
        // Set timer start
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();

        // Select what the user wants to do a run the code
        repeat = func_selection();


        // Stop timer and output
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "elapsed time: " << elapsed_seconds.count() << std::endl;

        //std::cout << superdie.size() << std::endl << superdie[5].amount << std::endl << superdie[superdie.size() - 1].amount << std::endl;
    }
}

// Ideas:
// For crit with possible adv/dis and/or elvenluck:
// Highest z of xdy =  1-((1-(y-z+1)/y))^x)
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
// all possible dice throws in one vector
// 
// Meanthrow
// (All eyes on die / sides on die) * diceset

// Websites
// https://www.w3schools.com/cpp/cpp_conditions.asp
// https://www.programiz.com/cpp-programming/vectors
// https://stackoverflow.com/questions/8011887/how-can-i-create-multiple-objects-with-for-loop-in-c
// https://www.geeksforgeeks.org/multithreading-in-cpp/
// https://www.gigacalculator.com/calculators/dice-probability-calculator.php#two-six-sided
// https://www.geeksforgeeks.org/how-to-return-multiple-values-from-a-function-in-c-or-cpp/
// https://docs.google.com/document/d/11eTMZPPxWXHY0rQEhK1msO-40BcCGrzArSl4GX4CiJE/edit#
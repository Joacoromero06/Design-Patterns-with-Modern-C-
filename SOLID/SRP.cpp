/*                  Act 1: The "God Object" (The Anti-Pattern)
*   The Scenario: You want to get the prototype working fast. You create one class to rule them all. 
*   It feels efficient at first because everything is in one place.

*   The Class: DeepBrain This class is a classic God Object. It knows too much and does too much.

*   The Code Smell: Look at how many different library headers we have to include.
*   That is your first clue that this class is confused about its identity.
*/
#include <vector>
#include <iostream> // file I/O
#include <fstream>  // logging
#include <string>   // file parsing
#include <cmath>    // math

class DeepBrain{
public:
    std::vector<std::vector<float>> W;
    std::vector<float> B;
public:
    // Model architecture
    void init(int n_input, int n_output){
        W.resize()
    }
};
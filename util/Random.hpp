#pragma once

#include <ctime>
#include <random>

/// A namespace to contain random number generation logic.
namespace Random {

    extern std::mt19937 generator;
    void seedGenerator(unsigned int seed);
    void seedGenerator();

    int getIntFromRange(int minimum, int maximum);
    float getFloatFromRange(float minimum, float maximum);

};

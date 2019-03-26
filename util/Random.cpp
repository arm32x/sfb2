#include "Random.hpp"

////////////////////////////////////////////////////////////////////////////////
/// The random number generator.
////////////////////////////////////////////////////////////////////////////////
std::mt19937 Random::generator;

////////////////////////////////////////////////////////////////////////////////
/// Seed the random number generator with an unsigned int.
/// 
/// @param seed The unsigned int to seed the generator with.
////////////////////////////////////////////////////////////////////////////////
void Random::seedGenerator(unsigned int seed) {
	generator.seed(seed);
}

////////////////////////////////////////////////////////////////////////////////
/// Seed the random number generator with a (typically) hardware-based random
/// number generator.  On some platforms (for example MinGW), this is not
/// hardware-based.
////////////////////////////////////////////////////////////////////////////////
void Random::seedGenerator() {
	// Create a (typically) hardware-based random number generator.
	std::random_device hardwareGenerator;
	// Use a value created by that generator to seed the main generator.
	seedGenerator(hardwareGenerator());
}

////////////////////////////////////////////////////////////////////////////////
/// Generate a random integer from the range specified.
///
/// @param minimum The minimum number that can generate, inclusive.
/// @param maximum The maximum number that can generate, inclusive.
/// @return A random integer in the given range.
////////////////////////////////////////////////////////////////////////////////
int Random::getIntFromRange(int minimum, int maximum) {
    std::uniform_int_distribution<int> dist(minimum, maximum);
    return dist(generator);
}

////////////////////////////////////////////////////////////////////////////////
/// Generate a random float from the range specified.
///
/// @param minimum The minimum number that can generate, inclusive.
/// @param maximum The maximum number that can generate, inclusive.
/// @return A random float in the given range.
////////////////////////////////////////////////////////////////////////////////
float Random::getFloatFromRange(float minimum, float maximum) {
    std::uniform_real_distribution<float> dist(minimum, maximum);
    return dist(generator);
}

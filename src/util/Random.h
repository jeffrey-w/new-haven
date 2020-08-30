#pragma once

#include <random>

// A facility for generating random integers.
namespace Random {

// Returns a random integer between the specified origin and bound (inclusive).
int next(int, int);

// A random number generator.
extern std::minstd_rand generator;

} // namespace Random

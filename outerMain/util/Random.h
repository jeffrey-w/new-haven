#pragma once

#include <random>

// A facility for generating random integers.
class Random {

public:

	// Returns a random integer between the specified origin and bound (inclusive).
	static int next(int, int);

	// Suppress default constructor.
	Random() = delete;
	// Suppress copy constructor.
	Random(Random&) = delete;

private:

	static std::minstd_rand GENERATOR;

};

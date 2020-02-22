#pragma once

#include <random>

class Random {

public:

	Random() = delete;
	Random(Random&) = delete;
	static int next(int, int);

private:

	static std::minstd_rand generator;

};

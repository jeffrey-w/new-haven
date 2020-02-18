#include <chrono>

#include "Random.h"

std::minstd_rand* Random::generator = new std::minstd_rand(std::chrono::system_clock::now().time_since_epoch().count());

int Random::next(int origin, int bound) {
	std::uniform_int_distribution<int> dist(origin, bound);
	return dist(generator);
}

#include <chrono>

#include "Random.h"

using std::chrono::system_clock;
using std::minstd_rand;

minstd_rand Random::generator(minstd_rand(system_clock::now().time_since_epoch().count()));

int Random::next(int origin, int bound) {
	std::uniform_int_distribution<int> dist(origin, bound);
	return dist(generator);
}

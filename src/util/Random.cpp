#include <chrono>

#include "Random.h"

using std::minstd_rand;
using std::chrono::system_clock;

minstd_rand Random::generator(system_clock::now().time_since_epoch().count());

int Random::next(int origin, int bound) {
    std::uniform_int_distribution<int> dist(origin, bound);
    return dist(generator);
}

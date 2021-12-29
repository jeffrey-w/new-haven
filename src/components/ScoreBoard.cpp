#include <stdexcept>

#include "ScoreBoard.h"

ScoreBoard::ScoreBoard() : villagers(0), built(0), unbuilt(0) {
}

ScoreBoard::ScoreBoard(const ScoreBoard& other) : ScoreBoard() {
    setScores(other.villagers, other.built, other.unbuilt);
}

int ScoreBoard::getVillagers() const {
    return villagers;
}

int ScoreBoard::getBuilt() const {
    return built;
}

int ScoreBoard::getUnbuilt() const {
    return unbuilt;
}

void ScoreBoard::setVillagers(int villagers) {
    this->villagers = validateScore(villagers);
}

void ScoreBoard::setBuilt(int built) {
    this->built = validateScore(built);
}

void ScoreBoard::setUnbuilt(int unbuilt) {
    this->unbuilt = validateScore(unbuilt);
}

void ScoreBoard::setScores(int villagers, int built, int unbuilt) {
    setVillagers(villagers);
    setBuilt(built);
    setUnbuilt(unbuilt);
}

int ScoreBoard::validateScore(int score) {
    if (score < 0) {
        throw std::invalid_argument("Score must be nonnegative.");
    }
    return score;
}

bool ScoreBoard::operator<(const ScoreBoard& other) const {
    if (villagers != other.villagers) {
        return villagers < other.villagers;
    }
    if (built != other.built) {
        return built < other.built;
    }
    return other.unbuilt < unbuilt;
}

bool ScoreBoard::operator==(const ScoreBoard& other) const {
    return villagers == other.villagers && built == other.built && unbuilt == other.unbuilt;
}

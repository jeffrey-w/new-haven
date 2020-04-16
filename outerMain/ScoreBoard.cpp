#include <stdexcept>
#include <sstream>
#include <string>

#include "ScoreBoard.h"

using std::list;
using std::map;
using std::string;

ScoreBoard::ScoreBoard() {
	_max = nullptr;
	scores = new map<long, Score*>();
}

ScoreBoard::ScoreBoard(const ScoreBoard& other) : ScoreBoard() {
	if (other._max) {
		_max = new Score(*other._max);
	}
	for (auto& entry : *other.scores) {
		(*scores)[entry.first] = new Score(*entry.second);
	}
}

ScoreBoard::~ScoreBoard() {
	for (auto& entry : *scores) {
		delete entry.second;
	}
	delete _max;
	delete scores;
}

void ScoreBoard::add(long id) {
	(*scores)[id] = new Score();
}

int ScoreBoard::maxVillagers() const {
	return *max()->villagers;
}

int ScoreBoard::maxBuilt() const {
	return *max()->built;
}

int ScoreBoard::maxUnbuilt() const {
	return *max()->unbuilt;
}

list<long> ScoreBoard::winners() {
	list<long> winners;
	Score* _max = max();
	for (auto& entry : *scores) {
		if (*entry.second == *_max) {
			winners.push_back(entry.first);
		}
	}
	return winners;
}

ScoreBoard::Score* ScoreBoard::max() const {
	if (!_max) {
		Score* _max = nullptr;
		for (auto& entry : *scores) {
			if (!_max || *_max < *entry.second) {
				_max = entry.second;
			}
		}
		if (_max) {
			this->_max = new Score(*_max);
		}
		else {
			throw std::runtime_error("No players on this board.");
		}
	}
	return _max;
}

void ScoreBoard::update(long id, int villagers, int built, int unbuilt) {
	if (!scores->count(id)) {
		throw std::invalid_argument("Player does not exist.");
	}
	Score* score = (*scores)[id];
	score->villagers = validateScore(villagers);
	score->built = validateScore(built);
	score->unbuilt = validateScore(unbuilt);
	score->notify();
	_max = nullptr;
}

int* ScoreBoard::validateScore(int score) {
	if (score < 0) {
		throw std::invalid_argument("Score must be nonnegative.");
	}
	return new int(score);
}

ScoreBoard::Score::Score() : Score(0, 0, 0) {}

ScoreBoard::Score::Score(const Score& other) :
	Score(*other.villagers, *other.built, *other.unbuilt) {}

ScoreBoard::Score::Score(int villagers, int built, int unbuilt) {
	this->villagers = new int(villagers);
	this->built = new int(built);
	this->unbuilt = new int(unbuilt);
}

ScoreBoard::Score::~Score() {
	delete villagers;
	delete built;
	delete unbuilt;
}

bool ScoreBoard::Score::operator<(const Score& other) const {
	if (*villagers != *other.villagers) {
		return *villagers < *other.villagers;
	}
	if (*built != *other.built) {
		return *built < *other.built;
	}
	return *other.unbuilt < *unbuilt;
}

bool ScoreBoard::Score::operator==(const Score& other) {
	return *villagers == *other.villagers && *built == *other.built && *unbuilt == *other.unbuilt;
}

string* ScoreBoard::Score::toString() const {
	std::ostringstream stream;
	stream << villagers << " " << built << " " << unbuilt;
	return new string(stream.str());
}

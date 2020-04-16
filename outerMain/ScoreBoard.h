#pragma once

#include <list>
#include <map>
#include <string>

#include "observers/Observable.h"

class ScoreBoard {

public:

	ScoreBoard();
	ScoreBoard(const ScoreBoard&);
	~ScoreBoard();
	void add(long);
	int maxVillagers() const;
	int maxBuilt() const;
	int maxUnbuilt() const;
	std::list<long> winners();
	void update(long, int, int, int);

private:

	struct Score : public Observable {

		int* villagers;
		int* built;
		int* unbuilt;

		Score();
		Score(int, int, int);
		Score(const Score&);
		~Score();

		bool operator<(const Score&) const;
		bool operator==(const Score&);

		std::string* toString() const override;

	};

	mutable Score* _max;
	std::map<long, Score*>* scores;

	Score* max() const;
	int* validateScore(int);

};


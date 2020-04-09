#pragma once

#include <set>

#include "Observer.h"

class Observable {

public:

	Observable();
	~Observable();
	void attach(Observer*);
	void notify();

private:

	std::set<Observer*>* observers;

};

#pragma once

#include <set>
#include <sstream>
#include <string>

#include "Observer.h"

class Observable {

public:

	template <class T>
	static std::string* toString(T& obj) {
		std::stringstream stream;
		stream << obj;
		return new std::string(stream.str());
	}

	Observable();
	~Observable();
	void attach(Observer*);
	void notify();

private:

	std::set<Observer*>* observers;

};

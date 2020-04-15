#pragma once

#include <set>
#include <string>

#include "Observer.h"

class Observable {

public:

	Observable();
	~Observable();
	void attach(Observer*);
	void notify();

	friend std::ostream& operator<<(std::ostream&, const Observable&);

protected:

	virtual std::string* toString() const = 0;

private:

	std::set<Observer*>* observers;

};

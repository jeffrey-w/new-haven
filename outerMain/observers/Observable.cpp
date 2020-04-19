#include <sstream>

#include "Observable.h"

using std::set;
using std::string;

Observable::Observable() {
	observers = new set<Observer*>();
}

Observable::~Observable() {
	delete observers;
}

void Observable::attach(Observer* observer) {
	if (!observer) {
		throw std::invalid_argument("Cannot be subject to the null observer.");
	}
	observers->insert(observer);
}

void Observable::detach(Observer* observer) {
	observers->erase(observer);
}

void Observable::notify() {
	for (auto& observer : *observers) {
		observer->update(toString());
	}
}

std::ostream& operator<<(std::ostream& stream, const Observable& o) {
	return stream << o.toString();
}

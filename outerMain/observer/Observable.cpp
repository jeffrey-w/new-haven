#include "Event.h"
#include "Observable.h"

using std::set;

Observable::Observable() {
	observers = new set<Observer*>();
}

Observable::~Observable() {
	for (auto& observer : *observers) {
		delete observer;
	}
	delete observers;
}

void Observable::attach(Observer* observer) {
	if(!observers->count(observer)) {
		observers->insert(observer);
	}
}

void Observable::notify() {
	for (auto& observer : *observers) {
		observer->update(Event(this));
	}
}

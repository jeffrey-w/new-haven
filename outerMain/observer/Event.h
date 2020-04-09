#pragma once

#include "Observable.h"

class Event {

public:

	Event(Observable*);
	~Event() = default;
	Observable* getSource();

private:

	Observable* source;

};
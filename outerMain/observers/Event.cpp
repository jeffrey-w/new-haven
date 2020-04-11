#include "Event.h"

Event::Event(Observable* source) {
	this->source = source;
}

Observable* Event::getSource() {
	return source;
}

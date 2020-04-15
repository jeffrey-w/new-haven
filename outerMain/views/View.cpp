#include <iostream>
#include <sstream>

#include "View.h"

using std::string;

View::View(Observable* o) {
	rep = Observable::toString(*o);
	o->attach(this);
}

View::~View() {
	delete rep;
}

void View::show() const {
	std::cout << *rep;
}

void View::update(string* rep) {
	delete this->rep;
	this->rep = rep;
}

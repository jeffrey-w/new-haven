#include <iostream>
#include <sstream>

#include "View.h"

using std::string;

View::View(Observable* o) {
	if (!o) {
		throw std::invalid_argument("Cannot observe the null subject.");
	}
	rep = nullptr;
	o->attach(this);
	o->notify();
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

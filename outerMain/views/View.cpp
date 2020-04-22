#include <iostream>

#include "View.h"

View::View(Observable* subject) {
	if (!subject) {
		throw std::invalid_argument("Cannot observe the null subject.");
	}
	subject->attach(this);
	this->subject = subject;
}

void View::show() const {
	std::cout << *subject;
}

void View::update() {
	show();
}

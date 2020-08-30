#include <iostream>

#include "View.h"

using std::string;

View::View(Observable* subject, string* header) {
    if (!subject) {
        throw std::invalid_argument("Cannot observe the null subject.");
    }
    if (!header) {
        throw std::invalid_argument("Cannot pass the null header");
    }
    subject->attach(this);
    this->subject = subject;
    this->header = header;
}

View::~View() {
    delete header;
}

void View::show(const string* header) const {
    std::cout << (header ? *header : *this->header) << '\n';
    std::cout << *subject;
}

void View::update() {
    show();
}

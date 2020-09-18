#include <iostream>

#include "View.h"

using std::string;

View::View(Observable* subject, const string& header) {
    if (!subject) {
        throw std::invalid_argument("Cannot observe the null subject.");
    }
    if (header == "") {
        throw std::invalid_argument("Cannot pass the empty string");
    }
    subject->attach(this);
    this->subject = subject;
    this->header = header;
}

void View::show(const string& header) const {
    std::cout << (header == "" ? this->header : header) << '\n';
    std::cout << *subject;
}

void View::update() {
    show();
}

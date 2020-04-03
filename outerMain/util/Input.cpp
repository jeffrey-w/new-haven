#include "Input.h"

Input::Input() {
	_cancelled = new bool(false);
}

Input::~Input() {
	delete _cancelled;
}

bool Input::cancelled() const {
	bool cancelled = *_cancelled;
	*_cancelled = false;
	return cancelled;
}

bool Input::decide(const std::string& prompt, bool predicate) {
    if (predicate) {
        bool decision, undecided = true;
        do {
            std::cout << prompt << " Y/n: ";
            switch (std::cin.get()) {
            case 'Y':
            case 'y':
                decision = true;
                undecided = false;
                break;
            case 'N':
            case 'n':
                decision = false;
                undecided = false;
                break;
            default:
                std::cout << "Did not understand. Try again.\n";
            }
            std::cin.ignore();
        } while (undecided);
        return decision;
    }
    return false;
}

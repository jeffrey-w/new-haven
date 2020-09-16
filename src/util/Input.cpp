#include "Input.h"

bool Input::decide(const std::string& prompt) {
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

Input::Input() {
    _cancelled = false;
}

bool Input::cancelled() const {
    return _cancelled;
}

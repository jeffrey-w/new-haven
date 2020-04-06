#pragma once

#include <iostream>
#include <sstream>
#include <string>

// A facility for getting user input.
class Input {

public:

    // Constructs a new Input object.
    Input();
    // Suppres copy constructor.
    Input(const Input&) = delete;
    // Destroys this Input.
    ~Input();
    // Returns true iff the previously polled input was cancelled.
    bool cancelled() const;
    // Prompts the user for and collects their input to a yes or no question.
    bool decide(const std::string&);
    // Gets user input and interprets it as the specified type.
	template <typename t>
	t get(const std::string& prompt, const std::string& fail, bool canCancel = false) {
        t result = t();
        std::string input;
        do {
            std::cout << prompt;
            if (canCancel) {
                std::cout << " (or press 'C' to cancel)";
            }
            std::cout << ": ";
            std::getline(std::cin, input);
            if (canCancel) {
                char c = std::stringstream(input).get();
                if (c == 'c' || c == 'C') {
                    *_cancelled = true;
                    break;
                }
            }
            if ((std::stringstream(input) >> result).fail()) {
                std::cerr << fail << " try again.\n";
            }
            else {
                break;
            }
        } while (true);
        return result;
	}

private:

	bool* _cancelled;

};


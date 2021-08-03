#pragma once

#include <iostream>
#include <sstream>
#include <string>

// A facility for getting user input.
class Input {

  public:
    // Prompts the user for and collects their input to the specified yes or no question.
    static bool decide(const std::string&);

    // Constructs a new Input object.
    Input();
    // Suppress copy constructor.
    Input(const Input&) = delete;
    // Returns true iff the previously polled input was cancelled.
    bool cancelled() const;

    // Gets user input and interprets it as the specified type. The specified prompt and fail messages inform the user what type of input is expected and whether an error has ocurred. The specified placeholder initializes the returned value. If specified, the user may cancel this prompt for input.
    template<typename T>
    T get(const std::string& prompt, const std::string& fail, T placeholder, bool canCancel = false) {
        T result = placeholder;
        std::string input;
        _cancelled = false;
    loop:
        std::cout << prompt;
        if (canCancel) {
            std::cout << " (or press 'C' to cancel)";
        }
        std::cout << ": ";
        std::getline(std::cin, input);
        if (canCancel) {
            char c = std::stringstream(input).get();
            if (c == 'c' || c == 'C') {
                _cancelled = true;
            }
        }
        if (!_cancelled && (std::stringstream(input) >> result).fail()) {
            std::cerr << fail << " try again.\n";
            goto loop;
        }
        return result;
    }

  private:
    bool _cancelled;
};

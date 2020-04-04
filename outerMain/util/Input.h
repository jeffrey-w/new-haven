#pragma once

#include <iostream>
#include <sstream>
#include <string>

class Input {

public:

    Input();
    Input(const Input&) = delete;
    ~Input();
    bool cancelled() const;
    bool decide(const std::string&, bool = true);

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
                std::cout << fail << " try again.\n";
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


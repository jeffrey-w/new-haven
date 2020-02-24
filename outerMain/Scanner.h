#pragma once

#include <fstream>

class Scanner {

public:

	Scanner() = delete;
	Scanner(std::string);
	Scanner(Scanner&) = delete;
	~Scanner();
	bool hasNext();
	int nextInt();
	char nextChar();
	void consume(char, std::string);

private:

	std::streampos* start;
	std::ifstream* stream;

	char advance();
	bool isDigit(char);
};


#include <string>

#include "Scanner.h"

using std::ifstream;
using std::string;

Scanner::Scanner(string path) {
	_line = new int(0);
	_col = new int(0);
	start = new std::streampos(0);
	stream = new ifstream(path);
	if (stream->fail()) {
		throw std::invalid_argument("Unable to open file at " + path + ".");
	}
}

Scanner::~Scanner() {
	delete start;
	delete stream;
}

int Scanner::line() const {
	return *_line;
}

int Scanner::column() const {
	return *_col;
}

bool Scanner::hasNext() {
	return stream->peek() != EOF;
}

void Scanner::consume(char expected, string msg) {
	if (stream->peek() != expected) {
		throw std::runtime_error(msg);
	}
	nextChar();
}

char Scanner::nextChar() {
	if (!hasNext()) {
		throw std::out_of_range("At end of file.");
	}
	char result = advance();
	*start = stream->tellg();
	return result;
}

bool Scanner::nextBool() {
	if (nextChar() == '\0') {
		return false;
	}
	return true;
}

int Scanner::nextInt() {
	if (!hasNext()) {
		throw std::out_of_range("At end of file.");
	}
	if (!isDigit(stream->peek())) {
		throw std::runtime_error("Unable to read an integer.");
	}
	size_t length, result;
	char* buffer;
	do {
		advance();
	} while (isDigit(stream->peek()));
	length = stream->tellg() - *start;
	*start = stream->tellg();
	buffer = new char[length + 1];
	stream->seekg(-length, std::ios_base::cur);
	stream->read(buffer, length);
	buffer[length] = '\0';
	result = std::stoi(buffer);
	delete[] buffer;
	buffer = nullptr;
	return result;
}

bool Scanner::isDigit(char c) {
	return c >= '0' && c <= '9';
}

char Scanner::advance() {
	char c;
	stream->read(&c, sizeof(char));
	if (c == '\n') {
		(*_line)++;
		*_col = 0;
	}
	else {
		(*_col)++;
	}
	return c;
}

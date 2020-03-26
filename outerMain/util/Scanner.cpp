#include <string>

#include "Debug.h"
#include "Scanner.h"

using std::ifstream;
using std::string;

Scanner::Scanner(const string& path) {
	_line = new int(1);
	_col = new int(1);
	stream = new ifstream(path);
	if (stream->fail()) {
		throw std::invalid_argument("Unable to open file at " + path + ".");
	}
}

Scanner::~Scanner() {
	delete _line;
	delete _col;
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

void Scanner::consume(char expected, const string& msg) {
	if (stream->peek() != expected) {
		throw std::runtime_error(msg);
	}
	advance();
}

char Scanner::nextChar() {
	if (!hasNext()) {
		throw std::out_of_range("At end of file.");
	}
	return advance();
}

bool Scanner::nextBool() {
	if (nextChar() == '\0') {
		return false;
	}
	return true;
}

int Scanner::nextInt() {
	int length = 0, result;
	char* buffer;
	if (!hasNext()) {
		throw std::out_of_range("At end of file.");
	}
	if (stream->peek() == '-') {
		advance();
		length++;
	}
	if (!isDigit(stream->peek())) {
		if (length) {
			stream->seekg(-length, std::ios_base::cur);
		}
		throw std::runtime_error("Unable to read an integer.");
	}
	do {
		advance();
		length++;
	} while (isDigit(stream->peek()));
	if (stream->eof()) {
		stream->seekg(0, stream->end);
	}
	buffer = new char[(uint64_t)length + 1];
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
	char c = stream->get();
	if (c == '\n') {
		(*_line)++;
		*_col = 1;
	}
	else {
		(*_col)++;
	}
	return c;
}

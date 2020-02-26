#include <string>

#include "Scanner.h"

using std::ifstream;
using std::string;

Scanner::Scanner(string path) {
	start = new std::streampos(0);
	stream = new ifstream(path);
	if (stream->fail()) {
		throw new std::exception(); // TODO need richer exception type
	}
}

Scanner::~Scanner() {
	delete start;
	delete stream;
}

bool Scanner::hasNext() {
	return stream->peek() != EOF;
}

void Scanner::consume(char expected, string msg) {
	if (stream->peek() != expected) {
		throw std::exception(); // TODO pass msg here; need richer exception type
	}
	nextChar();
}

char Scanner::nextChar() {
	if (!hasNext()) {
		throw new std::exception(); // TODO need richer exception type
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
	if (!hasNext() || !isDigit(stream->peek())) {
		throw new std::exception(); // TODO need richer exception type
	}
	int length, result;
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
	return c;
}

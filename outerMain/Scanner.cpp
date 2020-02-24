#include <string>

#include "Scanner.h"

using std::ifstream;
using std::string;

Scanner::Scanner(string path) {
	stream = new ifstream(path);
	if (stream->fail()) {
		throw new std::exception(); // TODO need richer exception type
	}
	start = new std::streampos(0);
}

Scanner::~Scanner() {
	delete start;
	delete stream;
}

bool Scanner::hasNext() {
	return stream->eof();
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
	buffer = new char[length + 1];
	stream->read(buffer, length);
	buffer[length] = '\0';
	result = std::stoi(buffer);
	delete[] buffer;
	buffer = nullptr;
	*start = stream->tellg();
	return result;
}

bool Scanner::isDigit(char c) {
	return c >= '0' && c <= '9';
}

char Scanner::nextChar() {
	if (!hasNext()) {
		throw new std::exception(); // TODO need richer exception type
	}
	char result = advance();
	*start = stream->tellg();
	return result;
}

void Scanner::consume(char expected, string msg) {
	if (stream->peek() != expected) {
		throw std::exception(); // TODO pass msg here; need richer exception type
	}
	advance();
}

char Scanner::advance() {
	char c;
	stream->read(&c, sizeof(char));
	return c;
}

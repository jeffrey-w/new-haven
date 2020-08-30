#pragma once

#include <fstream>

// A utility to read the contents of a file.
class Scanner {

  public:
    // Suppress default constructor.
    Scanner() = delete;
    // Constructs a new Scanner object from the specified file path. Throws an exception if the
    // file at the specified path cannot be opened.
    Scanner(const std::string &);
    // Suppress copy constructor.
    Scanner(Scanner &) = delete;
    // Destroys this Scanner.
    ~Scanner();
    // Returns the line number of the file specified at the creation of this Scanner that it is
    // currently at.
    int line() const;
    // Returns the column number of the file specified at the creation of this Scanner that is is
    // Currently at.
    int column() const;
    // Returns true iff the file specified at the creation of this Scanner has not been entirely
    // consumed.
    bool hasNext();
    // Reads the next character of the file specified at the creation of this Scanner and matches
    // it against the specified character. Throws an exception initialized with the specified
    // message if the characters do not match.
    void consume(char, const std::string &);
    // Returns the next character of the file specified at the ceration of this Scanner. Throws an
    // exception if the file has been consumed.
    char nextChar();
    // Returns the next character of the file specified at the creation of this Scanner,
    // interpreted as a boolean value. Throws an exception if the file has been consumed.
    bool nextBool();
    // Reads the next sequence of bytes of the file specified at the creation of this Scanner that
    // can be interpreted as an integer, and returns them as such. Throws an exception if the file
    // has been consumed or the next character of the file cannot be interpreted as an integer.
    int nextInt();

  private:
    int *_line;
    int *_col;
    std::ifstream *stream;

    char advance();
    bool isDigit(char);
};

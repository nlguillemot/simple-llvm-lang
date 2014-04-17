#ifndef SIMPLE_LEXER_HPP
#define SIMPLE_LEXER_HPP

#include "token.hpp"

#include <istream>
#include <ostream>
#include <set>
#include <string>

class Lexer
{
public:
    // the stream from which tokens are read.
    std::istream& InputStream;

    // The current line in the InputStream. Starts at 1.
    int CurrentLine;

    // Initially stores the first token in inputStream, a Invalid token if something horrible happens.
    // The lifetime of data in tokens is valid until the Lexer that generated them is destroyed.
    Token CurrentToken;

    // Using a stable set allows references to strings it contains
    // to be referred to from the outside (ie. through TokenType::AsString) without getting broken.
    std::set<std::string> StringSet;

    // builds a lexer which will draw tokens from the given stream of characters.
    Lexer(std::istream& inputStream);

    // Update CurrentToken and CurrentLine based by reading from InputStream
    // throws if there is an error in reading. Sets CurrentToken to EOF if no reading is left.
    void GetNext();
};

// Reads all tokens from one stream and writes their human-friendly string representation to another.
void WriteTokens(std::istream& is, std::ostream& os);

#endif // SIMPLE_LEXER_HPP

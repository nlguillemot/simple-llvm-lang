#ifndef SIMPLE_TOKEN_HPP
#define SIMPLE_TOKEN_HPP

#include <ostream>

// unique representations for the tokens accepted by the lexer.
enum class TokenType
{
    // special tokens
    Invalid,
    EndOfFile,
    Whitespace,
    // tokens used as factors
    Identifier, // AsString: the name of the identifier.
    Integer,    // AsInt: The numeric value of the integer.
    // keywords
    Local,
    // operators
    OpAssign
};

// discriminated union type for tokens
struct Token
{
    // The value of Type determines what kind of token it is.
    // It also determines which field (if any) of the discriminated union are valid.
    TokenType Type;

    union
    {
        const char* AsString;
        int AsInt;
    };

    Token(TokenType type)
        : Type(type)
    { }

    Token(TokenType type, const char* stringRep)
        : Type(type)
        , AsString(stringRep)
    { }

    Token(TokenType type, int intRep)
        : Type(type)
        , AsInt(intRep)
    { }
};

// prints human-friendly representation of token (for debugging)
std::ostream& operator<<(std::ostream& os, const Token& t);

#endif // SIMPLE_TOKEN_HPP

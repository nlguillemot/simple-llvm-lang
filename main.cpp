#include <iostream>
#include <cctype>
#include <string>
#include <set>
#include <functional>
#include <memory>

enum TokenType
{
    TT_WHITESPACE,
    TT_IDENTIFIER,
    TT_INTEGER,
    TT_VAR,
    TT_ASSIGN,
    TT_EOF,
    TT_UNKNOWN
};

struct Token
{
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

    TokenType Type;

    union
    {
        const char* AsString;
        int AsInt;
    };
};


std::ostream& operator<<(std::ostream& os, const Token& t)
{
    switch (t.Type)
    {
    case TT_WHITESPACE: os << "<wspace>"; break;
    case TT_IDENTIFIER: os << "<id(" << t.AsString << ")>"; break;
    case TT_INTEGER: os << "<int(" << t.AsInt << ")>"; break;
    case TT_VAR: os << "<var>"; break;
    case TT_ASSIGN: os << "<=>"; break;
    case TT_EOF: os << "<EOF>"; break;
    case TT_UNKNOWN: os << "<Unknown>"; break;
    default: os << "<???>"; break;
    }

    return os;
}

class Lexer
{
public:
    std::istream& InputStream;
    int CurrentLine;
    Token CurrentToken;
    std::set<std::string> StringSet;

    Lexer(std::istream& is)
        : InputStream(is)
        , CurrentLine(1)
        , CurrentToken(TT_UNKNOWN)
    {
    }

    void GetNext()
    {
        char nextChar = InputStream.peek();

        if (!InputStream)
        {
            CurrentToken = Token(TT_EOF);
            return;
        }

        if (std::isspace(nextChar))
        {
            CurrentToken = Token(TT_WHITESPACE);

            while (std::isspace(nextChar))
            {
                InputStream.get();
                if (nextChar == '\n') CurrentLine++;
                nextChar = InputStream.peek();
            }

            return;
        }
        else if (std::isalpha(nextChar))
        {
            std::string id;
            while (std::isalnum(nextChar))
            {
                InputStream.get();
                id += nextChar;
                nextChar = InputStream.peek();
            }

            auto stringit = StringSet.insert(std::move(id)).first;
            if (*stringit == "var")
            {
                CurrentToken = Token(TT_VAR);
            }
            else
            {
                const char* asString = stringit->c_str();
                CurrentToken = Token(TT_IDENTIFIER, asString);
            }

            return;
        }
        else if (std::isdigit(nextChar))
        {
            std::string digits;
            while (std::isdigit(nextChar)
                   || (digits.size() == 1
                       && (nextChar == 'x' || nextChar == 'X')))
            {
                InputStream.get();
                digits += nextChar;
                nextChar = InputStream.peek();
            }

            auto asInt = std::stoi(digits, 0, 0);
            CurrentToken = Token(TT_INTEGER, asInt);
            return;
        }
        else if (nextChar == '=')
        {
            InputStream.get();
            CurrentToken = Token(TT_ASSIGN);
            return;
        }
        else
        {
            throw std::runtime_error(std::string("Invalid character ") + nextChar + " at line " + std::to_string(CurrentLine));
        }
    }
};

void WriteTokens(std::istream& is, std::ostream& os)
{
    Lexer lex(is);
    int currentLine = 1;

    do
    {
        lex.GetNext();
        for (int i = currentLine; i < lex.CurrentLine; i++)
        {
            os << '\n';
        }
        currentLine = lex.CurrentLine;

        os << lex.CurrentToken << ' ';
    } while (lex.CurrentToken.Type != TT_EOF);

    os << '\n';
}

void Parse(Lexer& tokenStream)
{
    do
    {
        tokenStream.GetNext();
    } while (tokenStream.CurrentToken.Type != TT_EOF);
}

int main(int argc, char* argv[])
{
    Lexer lexer(std::cin);
    Parse(lexer);
}

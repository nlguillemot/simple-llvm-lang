#include "lexer.hpp"

#include <cctype>
#include <exception>
#include <stdexcept>

Lexer::Lexer(std::istream& inputStream)
    : InputStream(inputStream)
    , CurrentLine(1)
    , CurrentToken(TokenType::Invalid)
{
    // Read the first token
    GetNext();
}

void Lexer::GetNext()
{
    char nextChar = InputStream.peek();

    if (!InputStream)
    {
        CurrentToken = Token(TokenType::EndOfFile);
        return;
    }

    if (std::isspace(nextChar))
    {
        CurrentToken = Token(TokenType::Whitespace);

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
        if (*stringit == "local")
        {
            CurrentToken = Token(TokenType::KwLocal);
        }
        else
        {
            const char* asString = stringit->c_str();
            CurrentToken = Token(TokenType::Identifier, asString);
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
        CurrentToken = Token(TokenType::Integer, asInt);

        return;
    }
    else if (nextChar == '=')
    {
        InputStream.get();

        CurrentToken = Token(TokenType::OpAssign);

        return;
    }
    else
    {
        throw std::runtime_error(std::string("Invalid character ") + nextChar + " at line " + std::to_string(CurrentLine));
    }
}

void WriteTokens(std::istream& is, std::ostream& os)
{
    Lexer lexer(is);
    int currentLine = 1;

    do
    {
        lexer.GetNext();

        for (int i = currentLine; i < lexer.CurrentLine; i++)
        {
            os << '\n';
        }

        currentLine = lexer.CurrentLine;

        os << lexer.CurrentToken << ' ';

    } while (lexer.CurrentToken.Type != TokenType::EndOfFile);

    os << '\n';
}

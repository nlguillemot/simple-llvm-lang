#include "token.hpp"

std::ostream& operator<<(std::ostream& os, const Token& t)
{
    switch (t.Type)
    {
    case TokenType::Invalid:    os << "<invalid>";                  break;
    case TokenType::EndOfFile:  os << "<eof>";                      break;
    case TokenType::Whitespace: os << "<wspace>";                   break;
    case TokenType::Identifier: os << "<id(" << t.AsString << ")>"; break;
    case TokenType::Integer:    os << "<int(" << t.AsInt << ")>";   break;
    case TokenType::KwLocal:    os << "<local>";                    break;
    case TokenType::OpAssign:   os << "<=>";                        break;
    default:                    os << "<???>";                      break;
    }

    return os;
}

#ifndef SIMPLE_PARSER_HPP
#define SIMPLE_PARSER_HPP

#include "ast.hpp"
#include "token.hpp"

class Lexer;

class Parser
{
public:
    // The lexer from which the parser will draw tokens.
    Lexer& TokenStream;

    // Constructs a parser that creates a parse tree from tokens.
    Parser(Lexer& tokenStream);

    // Reads tokens from the lexer and returns an AST for a module.
    std::unique_ptr<ModuleAST> AcceptModule();

    // Reads tokens from the lexer and returns an AST for a statement.
    std::unique_ptr<StatementAST> AcceptStatement();

    // Reads tokens from the lexer and returns an AST for a factor.
    std::unique_ptr<FactorAST> AcceptFactor();

    // Reads tokens from the lexer and returns an AST for an identifier.
    std::unique_ptr<IdentifierAST> AcceptIdentifier();

    // Reads tokens from the lexer and returns an AST for an integer.
    std::unique_ptr<IntegerAST> AcceptInteger();

    // Checks if the leading token is of the desired type and accepts it if it is.
    // returns true if there was any, false otherwise.
    bool AcceptOptionalTokenOfType(TokenType type);

    // Accepts the current token only if the current token has the given type. Throws otherwise.
    void AcceptMandatoryTokenOfType(TokenType type);

    // Checks that the current token is of the required type without eating it.
    // Returns true if it was the given type, false otherwise.
    bool CheckOptionalTokenOfType(TokenType type) const;

    // Checks that the current token is of the required type without eating it. Throws otherwise.
    void CheckMandatoryTokenOfType(TokenType type) const;
};

#endif // SIMPLE_PARSER_HPP

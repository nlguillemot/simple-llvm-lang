#include "parser.hpp"

#include "lexer.hpp"

Parser::Parser(Lexer& tokenStream)
    : TokenStream(tokenStream)
{ }

std::unique_ptr<ModuleAST> Parser::AcceptModule()
{
    std::unique_ptr<ModuleAST> pModule(new ModuleAST);

    // Read any whitespace before the first statement.
    AcceptOptionalTokenOfType(TokenType::Whitespace);

    // Read the whole file in this loop.
    while (!CheckOptionalTokenOfType(TokenType::EndOfFile))
    {
        // If there's still more in the file, it should be a statement.
        pModule->Statements.push_back(AcceptStatement());

        // Get rid of any whitespace until the next statement.
        AcceptOptionalTokenOfType(TokenType::Whitespace);
    }

    return pModule;
}

std::unique_ptr<StatementAST> Parser::AcceptStatement()
{
    std::unique_ptr<StatementAST> pStatement;

    // For local variable declarations.
    if (CheckOptionalTokenOfType(TokenType::Local))
    {
        std::unique_ptr<LocalDeclStatementAST> pLocalDeclStatement(new LocalDeclStatementAST);

        // Accept the "local" keyword.
        AcceptMandatoryTokenOfType(TokenType::Local);

        // Ensure whitespace between "local" and the identifier it declares.
        AcceptMandatoryTokenOfType(TokenType::Whitespace);

        // Read in the declared identifier.
        pLocalDeclStatement->DeclaredIdentifier = AcceptIdentifier();

        // Set the statement to that declaration.
        pStatement = std::move(pLocalDeclStatement);
    }
    else if (CheckOptionalTokenOfType(TokenType::Identifier))
    {
        std::unique_ptr<AssignmentStatementAST> pAssignmentStatement(new AssignmentStatementAST);

        // Accept the identifier for the left side of the assignment.
        pAssignmentStatement->LeftSide = AcceptIdentifier();

        // There may be whitespace between the identifier and the "=".
        AcceptOptionalTokenOfType(TokenType::Whitespace);

        // Eat the "=".
        AcceptMandatoryTokenOfType(TokenType::OpAssign);

        // There may be whitespace between the "=" and the next factor.
        AcceptOptionalTokenOfType(TokenType::Whitespace);

        // Accept the factor which will be made the value of the left side.
        pAssignmentStatement->RightSide = AcceptFactor();

        // Build a statement from that assignment.
        pStatement = std::move(pAssignmentStatement);
    }
    else
    {
        throw std::runtime_error("Could not parse statement.");
    }

    // Accept any trailing whitespace.
    AcceptOptionalTokenOfType(TokenType::Whitespace);

    return pStatement;
}

std::unique_ptr<FactorAST> Parser::AcceptFactor()
{
    std::unique_ptr<FactorAST> pFactor;

    if (CheckOptionalTokenOfType(TokenType::Identifier))
    {
        std::unique_ptr<IdentifierFactorAST> pIdentifierFactor(new IdentifierFactorAST);

        pIdentifierFactor->Identifier = AcceptIdentifier();

        pFactor = std::move(pIdentifierFactor);
    }
    else if (CheckOptionalTokenOfType(TokenType::Integer))
    {
        std::unique_ptr<IntegerFactorAST> pIntegerFactor(new IntegerFactorAST);

        pIntegerFactor->Integer = AcceptInteger();

        pFactor = std::move(pIntegerFactor);
    }
    else
    {
        throw std::runtime_error("Could not parse factor.");
    }

    return pFactor;
}

std::unique_ptr<IdentifierAST> Parser::AcceptIdentifier()
{
    if (!CheckOptionalTokenOfType(TokenType::Identifier))
    {
        throw std::runtime_error("Could not parse identifier.");
    }

    std::unique_ptr<IdentifierAST> pIdentifier(new IdentifierAST);

    pIdentifier->IdentifierName = TokenStream.CurrentToken.AsString;

    TokenStream.GetNext();

    return pIdentifier;
}

std::unique_ptr<IntegerAST> Parser::AcceptInteger()
{
    if (!CheckOptionalTokenOfType(TokenType::Integer))
    {
        throw std::runtime_error("Could not parse integer.");
    }

    std::unique_ptr<IntegerAST> pInteger(new IntegerAST);

    pInteger->IntegerValue = TokenStream.CurrentToken.AsInt;

    TokenStream.GetNext();

    return pInteger;
}

bool Parser::AcceptOptionalTokenOfType(TokenType type)
{
    bool checkResult = CheckOptionalTokenOfType(type);

    if (checkResult)
    {
        TokenStream.GetNext();
    }

    return checkResult;
}

void Parser::AcceptMandatoryTokenOfType(TokenType type)
{
    CheckMandatoryTokenOfType(type);

    TokenStream.GetNext();
}

bool Parser::CheckOptionalTokenOfType(TokenType type) const
{
    return TokenStream.CurrentToken.Type == type;
}

void Parser::CheckMandatoryTokenOfType(TokenType type) const
{
    if (!CheckOptionalTokenOfType(type))
    {
        throw std::runtime_error("Incorrect token type");
    }
}

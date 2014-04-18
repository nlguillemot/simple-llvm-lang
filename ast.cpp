#include "ast.hpp"

void IdentifierAST::Accept(IASTVisitor& visitor)
{
    visitor.Visit(*this);
}

void IntegerAST::Accept(IASTVisitor& visitor)
{
    visitor.Visit(*this);
}

void FactorAST::Accept(IASTVisitor& visitor)
{
    visitor.Visit(*this);
}

void IdentifierFactorAST::Accept(IASTVisitor& visitor)
{
    visitor.Visit(*this);

    if (Identifier)
    {
        Identifier->Accept(visitor);
    }
}

void IntegerFactorAST::Accept(IASTVisitor& visitor)
{
    visitor.Visit(*this);

    if (Integer)
    {
        Integer->Accept(visitor);
    }
}

void StatementAST::Accept(IASTVisitor& visitor)
{
    visitor.Visit(*this);
}

void LocalDeclarationStatementAST::Accept(IASTVisitor& visitor)
{
    visitor.Visit(*this);

    if (DeclaredIdentifier)
    {
        DeclaredIdentifier->Accept(visitor);
    }
}

void AssignmentStatementAST::Accept(IASTVisitor& visitor)
{
    visitor.Visit(*this);

    if (LeftSide)
    {
        LeftSide->Accept(visitor);
    }

    if (RightSide)
    {
        RightSide->Accept(visitor);
    }
}

void ModuleAST::Accept(IASTVisitor& visitor)
{
    visitor.Visit(*this);

    for (std::unique_ptr<StatementAST>& pStatement : Statements)
    {
        if (pStatement)
        {
            pStatement->Accept(visitor);
        }
    }
}

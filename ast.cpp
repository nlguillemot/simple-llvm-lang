#include "ast.hpp"

template<class T>
struct ScopedVisit
{
    T& Visited;
    IASTVisitor& Visitor;

    ScopedVisit(T& visited, IASTVisitor& visitor)
        : Visited(visited)
        , Visitor(visitor)
    {
        Visitor.Visit(Visited);
    }

    ~ScopedVisit()
    {
        Visitor.Exit(Visited);
    }
};

void IdentifierAST::Accept(IASTVisitor& visitor)
{
    ScopedVisit<IdentifierAST> visit(*this, visitor);
}

void IntegerAST::Accept(IASTVisitor& visitor)
{
    ScopedVisit<IntegerAST> visit(*this, visitor);
}

void FactorAST::Accept(IASTVisitor& visitor)
{
    ScopedVisit<FactorAST> visit(*this, visitor);
}

void IdentifierFactorAST::Accept(IASTVisitor& visitor)
{
    ScopedVisit<IdentifierFactorAST> visit(*this, visitor);

    if (Identifier)
    {
        Identifier->Accept(visitor);
    }
}

void IntegerFactorAST::Accept(IASTVisitor& visitor)
{
    ScopedVisit<IntegerFactorAST> visit(*this, visitor);

    if (Integer)
    {
        Integer->Accept(visitor);
    }
}

void StatementAST::Accept(IASTVisitor& visitor)
{
    ScopedVisit<StatementAST> visit(*this, visitor);
}

void LocalDeclarationStatementAST::Accept(IASTVisitor& visitor)
{
    ScopedVisit<LocalDeclarationStatementAST> visit(*this, visitor);

    if (DeclaredIdentifier)
    {
        DeclaredIdentifier->Accept(visitor);
    }
}

void AssignmentStatementAST::Accept(IASTVisitor& visitor)
{
    ScopedVisit<AssignmentStatementAST> visit(*this, visitor);

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
    ScopedVisit<ModuleAST> visit(*this, visitor);

    for (std::unique_ptr<StatementAST>& pStatement : Statements)
    {
        if (pStatement)
        {
            pStatement->Accept(visitor);
        }
    }
}

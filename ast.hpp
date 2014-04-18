#ifndef SIMPLE_AST_HPP
#define SIMPLE_AST_HPP

#include <memory>
#include <vector>

class IASTVisitor;

// Common base class for all abstract syntax trees.
class IAST
{
public:
    virtual ~IAST() = default;

    virtual void Accept(IASTVisitor& visitor) = 0;
};

// The abstract syntax tree for an identifier.
class IdentifierAST : public IAST
{
public:
    const char* IdentifierName;

    void Accept(IASTVisitor& visitor) override;
};

// The abstract syntax tree for an integer.
class IntegerAST : public IAST
{
public:
    int IntegerValue;

    void Accept(IASTVisitor& visitor) override;
};

// The abstract syntax tree for a factor.
class FactorAST : public IAST
{
public:
    void Accept(IASTVisitor& visitor) override;
};

// A factor which is a single identifier.
class IdentifierFactorAST : public FactorAST
{
public:
    std::unique_ptr<IdentifierAST> Identifier;

    void Accept(IASTVisitor& visitor) override;
};

// A factor which is a single integer.
class IntegerFactorAST : public FactorAST
{
public:
    std::unique_ptr<IntegerAST> Integer;

    void Accept(IASTVisitor& visitor) override;
};

// The abstract syntax tree for a statement.
class StatementAST : public IAST
{
public:
    void Accept(IASTVisitor& visitor) override;
};

// A statement which declares a new local variable.
class LocalDeclarationStatementAST : public StatementAST
{
public:
    std::unique_ptr<IdentifierAST> DeclaredIdentifier;

    void Accept(IASTVisitor& visitor) override;
};

// A statement which assigns a value to a variable.
class AssignmentStatementAST : public StatementAST
{
public:
    std::unique_ptr<IdentifierAST> LeftSide;
    std::unique_ptr<FactorAST> RightSide;

    void Accept(IASTVisitor& visitor) override;
};

// AST containing the code for a module. (aka. a translation/compilation unit)
class ModuleAST : public IAST
{
public:
    // A list of all the top-level statements in the module.
    std::vector<std::unique_ptr<StatementAST>> Statements;

    void Accept(IASTVisitor& visitor) override;
};

// Used for traversing the AST
class IASTVisitor
{
public:
    virtual ~IASTVisitor() = default;

    // module
    virtual void Visit(ModuleAST& module)                                  = 0;
    virtual void Exit(ModuleAST& module)                                   = 0;

    // statements
    virtual void Visit(StatementAST& statement)                                   = 0;
    virtual void Exit(StatementAST& statement)                                    = 0;
    virtual void Visit(LocalDeclarationStatementAST& localDeclarationStatement)   = 0;
    virtual void Exit(LocalDeclarationStatementAST& localDeclarationStatement)    = 0;
    virtual void Visit(AssignmentStatementAST& assignmentStatement)               = 0;
    virtual void Exit(AssignmentStatementAST& assignmentStatement)                = 0;

    // factors
    virtual void Visit(FactorAST& factor)                                  = 0;
    virtual void Exit(FactorAST& factor)                                   = 0;
    virtual void Visit(IdentifierFactorAST& identifierFactor)              = 0;
    virtual void Exit(IdentifierFactorAST& identifierFactor)               = 0;
    virtual void Visit(IntegerFactorAST& integerFactor)                    = 0;
    virtual void Exit(IntegerFactorAST& integerFactor)                     = 0;

    // basic terminals
    virtual void Visit(IdentifierAST& identifier)                          = 0;
    virtual void Exit(IdentifierAST& identifier)                           = 0;
    virtual void Visit(IntegerAST& integer)                                = 0;
    virtual void Exit(IntegerAST& integer)                                 = 0;
};

#endif // SIMPLE_AST_HPP

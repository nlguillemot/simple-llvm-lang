#ifndef SIMPLE_AST_HPP
#define SIMPLE_AST_HPP

#include <memory>
#include <vector>

// Common base class for all abstract syntax trees.
class IAST
{
public:
    virtual ~IAST() = default;
};

// The abstract syntax tree for an identifier.
class IdentifierAST : public IAST
{
public:
    const char* IdentifierName;
};

class IntegerAST : public IAST
{
public:
    int IntegerValue;
};

// The abstract syntax tree for a factor.
class FactorAST : public IAST
{
};

// A factor which is a single identifier.
class IdentifierFactorAST : public FactorAST
{
public:
    std::unique_ptr<IdentifierAST> Identifier;
};

// A factor which is a single integer.
class IntegerFactorAST : public FactorAST
{
public:
    std::unique_ptr<IntegerAST> Integer;
};

// The abstract syntax tree for a statement.
class StatementAST : public IAST
{
};

// A statement which declares a new local variable.
class LocalDeclStatementAST : public StatementAST
{
public:
    std::unique_ptr<IdentifierAST> DeclaredIdentifier;
};

// A statement which assigns a value to a variable.
class AssignmentStatementAST : public StatementAST
{
public:
    std::unique_ptr<IdentifierAST> LeftSide;
    std::unique_ptr<FactorAST> RightSide;
};

// AST containing the code for a module. (aka. a translation/compilation unit)
class ModuleAST : public IAST
{
public:
    // A list of all the top-level statements in the module.
    std::vector<std::unique_ptr<StatementAST>> Statements;
};

#endif // SIMPLE_AST_HPP

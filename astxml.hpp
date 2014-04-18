#ifndef SIMPLE_ASTXML_HPP
#define SIMPLE_ASTXML_HPP

#include "ast.hpp"

#include <ostream>
#include <string>

class XMLWriterASTVisitor : public IASTVisitor
{
public:
    std::ostream& OutputStream;
    std::string CurrentIndent;

    XMLWriterASTVisitor(std::ostream& outputStream);

    // module
    void Visit(ModuleAST& module) override;
    void Exit(ModuleAST& module) override;

    // statements
    void Visit(StatementAST& statement) override;
    void Exit(StatementAST& statement) override;
    void Visit(LocalDeclarationStatementAST& localDeclarationStatement) override;
    void Exit(LocalDeclarationStatementAST& localDeclarationStatement) override;
    void Visit(AssignmentStatementAST& assignmentStatement) override;
    void Exit(AssignmentStatementAST& assignmentStatement) override;

    // factors
    void Visit(FactorAST& factor) override;
    void Exit(FactorAST& factor) override;
    void Visit(IdentifierFactorAST& identifierFactor) override;
    void Exit(IdentifierFactorAST& identifierFactor) override;
    void Visit(IntegerFactorAST& integerFactor) override;
    void Exit(IntegerFactorAST& integerFactor) override;

    // basic terminals
    void Visit(IdentifierAST& identifier) override;
    void Exit(IdentifierAST& identifier) override;
    void Visit(IntegerAST& integer) override;
    void Exit(IntegerAST& integer) override;

    // increase the depth of indentation by 1 unit.
    void PushIndent();

    // decrease the depth of indentation by 1 unit.
    void PopIndent();
};

#endif // SIMPLE_ASTXML_HPP

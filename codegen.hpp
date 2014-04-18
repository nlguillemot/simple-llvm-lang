#ifndef SIMPLE_CODEGEN_HPP
#define SIMPLE_CODEGEN_HPP

#include "ast.hpp"

#include <llvm/IR/IRBuilder.h>

class CodeGenASTVisitor : public IASTVisitor
{
public:
    llvm::LLVMContext& Context;
    llvm::Module& TargetModule;
    llvm::IRBuilder<> Builder;

    llvm::Function* MainFunction = nullptr;
    llvm::BasicBlock* MainBasicBlock = nullptr;

    std::map<std::string, llvm::Value*> LocalSymbolTable;

    // If we are in a local variable declaration, this will be non-null.
    // Its name will be given when the next IdentifierAST is visited.
    llvm::Value* CurrentLocalBeingDeclared = nullptr;

    // If we are in a binary operator, then this is non-null
    // and the binary operands are to be stored in the pair's members.
    std::unique_ptr<std::pair<llvm::Value*,llvm::Value*>> CurrentAssignmentOperands;

    CodeGenASTVisitor(llvm::Module& targetModule);

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
};

#endif // SIMPLE_CODEGEN_HPP

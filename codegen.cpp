#include "codegen.hpp"

#include <llvm/IR/Module.h>

#include <utility>

CodeGenASTVisitor::CodeGenASTVisitor(llvm::Module& targetModule)
    : Context(targetModule.getContext())
    , TargetModule(targetModule)
    , Builder(TargetModule.getContext())
{
}

void CodeGenASTVisitor::Visit(ModuleAST&)
{
    llvm::FunctionType* MainType = llvm::FunctionType::get(
                llvm::Type::getInt32Ty(Context),
                false);

    MainFunction = llvm::Function::Create(
                MainType,
                llvm::Function::ExternalLinkage,
                "main",
                &TargetModule);

    GlobalBasicBlock = llvm::BasicBlock::Create(
                Context,
                "entry",
                MainFunction);

    Builder.SetInsertPoint(GlobalBasicBlock);
}

void CodeGenASTVisitor::Exit(ModuleAST& module)
{
}

void CodeGenASTVisitor::Visit(StatementAST& statement)
{
}

void CodeGenASTVisitor::Exit(StatementAST& statement)
{
}

void CodeGenASTVisitor::Visit(LocalDeclarationStatementAST&)
{
    InDeclarationStatement = true;
}

void CodeGenASTVisitor::Exit(LocalDeclarationStatementAST&)
{
    InDeclarationStatement = false;
}

void CodeGenASTVisitor::Visit(AssignmentStatementAST&)
{
    InAssignmentStatement = true;
}

void CodeGenASTVisitor::Exit(AssignmentStatementAST&)
{
    InAssignmentStatement = false;
}

void CodeGenASTVisitor::Visit(FactorAST& factor)
{
}

void CodeGenASTVisitor::Exit(FactorAST& factor)
{
}

void CodeGenASTVisitor::Visit(IdentifierFactorAST& identifierFactor)
{
}

void CodeGenASTVisitor::Exit(IdentifierFactorAST& identifierFactor)
{
}

void CodeGenASTVisitor::Visit(IntegerFactorAST& integerFactor)
{
}

void CodeGenASTVisitor::Exit(IntegerFactorAST& integerFactor)
{
}

void CodeGenASTVisitor::Visit(IdentifierAST& identifier)
{
    if (InDeclarationStatement)
    {
        llvm::Type* IntType = llvm::Type::getInt32Ty(Context);

        CurrentDeclaredLocal = Builder.CreateAlloca(
                    IntType,
                    0,
                    identifier.IdentifierName);

        LocalSymbolTable.emplace(
                    std::make_pair(
                        identifier.IdentifierName,
                        CurrentDeclaredLocal));
    }
}

void CodeGenASTVisitor::Exit(IdentifierAST& identifier)
{
}

void CodeGenASTVisitor::Visit(IntegerAST& integer)
{
}

void CodeGenASTVisitor::Exit(IntegerAST& integer)
{
}

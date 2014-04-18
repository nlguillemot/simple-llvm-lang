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
    // The type of the main function
    llvm::FunctionType* MainType = llvm::FunctionType::get(
                llvm::Type::getInt32Ty(Context),
                false);

    // The whole program runs within the main function.
    MainFunction = llvm::Function::Create(
                MainType,
                llvm::Function::ExternalLinkage,
                "main",
                &TargetModule);

    // This block contains all the instructions within main.
    MainBasicBlock = llvm::BasicBlock::Create(
                Context,
                "entry",
                MainFunction);

    // The builder is used to add instructions to the main function's block.
    Builder.SetInsertPoint(MainBasicBlock);
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
    // The alloca instruction is used to push locals on the stack.
    // This pushes an anonymous local, which will be named in the visit of IdentifierAST
    CurrentLocalBeingDeclared = Builder.CreateAlloca(llvm::Type::getInt32Ty(Context));
}

void CodeGenASTVisitor::Exit(LocalDeclarationStatementAST&)
{
    CurrentLocalBeingDeclared = nullptr;
}

void CodeGenASTVisitor::Visit(AssignmentStatementAST& assignmentStatement)
{
}

void CodeGenASTVisitor::Exit(AssignmentStatementAST&)
{
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
    if (CurrentLocalBeingDeclared)
    {
        // If this is visited for the purpose of declaring a local variable,
        // give the local variable the same name as the identifier.
        CurrentLocalBeingDeclared->setName(identifier.IdentifierName);
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

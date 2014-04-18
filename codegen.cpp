#include "codegen.hpp"

#include <llvm/IR/Module.h>

#include <utility>

CodeGenASTVisitor::CodeGenASTVisitor(llvm::Module& targetModule)
    : Context(targetModule.getContext())
    , TargetModule(targetModule)
    , Builder(TargetModule.getContext())
{ }

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
    if (CurrentLocalBeingDeclared)
    {
        throw std::logic_error("Declaring a local while another local is being declared.");
    }

    // The alloca instruction is used to push locals on the stack.
    // This pushes an anonymous local, which will be named in the visit of IdentifierAST
    CurrentLocalBeingDeclared = Builder.CreateAlloca(llvm::Type::getInt32Ty(Context));
}

void CodeGenASTVisitor::Exit(LocalDeclarationStatementAST&)
{
    if (!CurrentLocalBeingDeclared || !CurrentLocalBeingDeclared->hasName())
    {
        throw std::logic_error("Local variable was not assigned a name.");
    }

    CurrentLocalBeingDeclared = nullptr;
}

void CodeGenASTVisitor::Visit(AssignmentStatementAST& assignmentStatement)
{
    // TODO: Think about compound binary operators like a = b + c

    CurrentAssignmentOperands.reset(new std::pair<llvm::Value*,llvm::Value*>);
}

void CodeGenASTVisitor::Exit(AssignmentStatementAST&)
{
    if (!CurrentAssignmentOperands)
    {
        throw std::logic_error("Expected assignment operands to be available.");
    }

    Builder.CreateStore(CurrentAssignmentOperands->second,
                        CurrentAssignmentOperands->first);

    CurrentAssignmentOperands = nullptr;
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
        if (CurrentLocalBeingDeclared->hasName())
        {
            throw std::logic_error("Local variable was named twice.");
        }

        // If this is visited for the purpose of declaring a local variable,
        // give the local variable the same name as the identifier.
        CurrentLocalBeingDeclared->setName(identifier.IdentifierName);

        LocalSymbolTable.emplace(std::make_pair(identifier.IdentifierName, CurrentLocalBeingDeclared));
    }
    else if (CurrentAssignmentOperands)
    {
        llvm::Value** pOperand = !CurrentAssignmentOperands->first ? &(CurrentAssignmentOperands->first)
                               : !CurrentAssignmentOperands->second ? &(CurrentAssignmentOperands->second)
                               : throw std::logic_error("No operands are unfulfilled.");

        *pOperand = LocalSymbolTable.at(identifier.IdentifierName);
    }
}

void CodeGenASTVisitor::Exit(IdentifierAST& identifier)
{
}

void CodeGenASTVisitor::Visit(IntegerAST& integer)
{
    if (CurrentAssignmentOperands)
    {
        llvm::Value** pOperand = !CurrentAssignmentOperands->first ? &(CurrentAssignmentOperands->first)
                               : !CurrentAssignmentOperands->second ? &(CurrentAssignmentOperands->second)
                               : throw std::logic_error("No operands are unfulfilled.");

        *pOperand = llvm::ConstantInt::get(
                    llvm::Type::getInt32Ty(Context),
                    integer.IntegerValue);
    }
}

void CodeGenASTVisitor::Exit(IntegerAST& integer)
{
}

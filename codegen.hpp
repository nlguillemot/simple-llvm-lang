#ifndef SIMPLE_CODEGEN_HPP
#define SIMPLE_CODEGEN_HPP

#include <llvm/IR/IRBuilder.h>

class CodeGenVisitor
{
public:
    llvm::Module* GeneratedModule;
    llvm::IRBuilder<> Builder;
    std::map<const char*, llvm::Value*> SymbolTable;

    CodeGenVisitor();
};

#endif // SIMPLE_CODEGEN_HPP

#include <iostream>
#include <fstream>

#include "lexer.hpp"
#include "parser.hpp"

#include "codegen.hpp"
#include "astxml.hpp"

#include <llvm/IR/Module.h>

void run(std::istream& inputStream)
{
    Lexer lexer(inputStream);

    Parser parser(lexer);

    std::unique_ptr<ModuleAST> pModule;

    try
    {
        pModule = parser.AcceptModule();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n'
                  << "Died on token: " << lexer.CurrentToken << '\n';
        throw;
    }

    XMLWriterASTVisitor xmlWriter(std::cout);
    pModule->Accept(xmlWriter);

    llvm::LLVMContext& llvmContext = llvm::getGlobalContext();
    llvm::Module llvmModule("simple", llvmContext);

    CodeGenASTVisitor codeGenerator(llvmModule);
    pModule->Accept(codeGenerator);

    llvmModule.dump();
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        const char* appName = argc >= 1 ? argv[0] : "simple";

        std::cout << "Usage: " << appName << " <file>\n";

        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile)
    {
        std::cout << "Could not open file \"" << argv[1] << "\"\n";
        return 2;
    }

    run(inputFile);
}

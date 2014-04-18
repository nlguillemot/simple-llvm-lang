#include <iostream>
#include <fstream>

#include "lexer.hpp"
#include "parser.hpp"

#include "astxml.hpp"

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

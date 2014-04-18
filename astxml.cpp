#include "astxml.hpp"

#include <stdexcept>

XMLWriterASTVisitor::XMLWriterASTVisitor(std::ostream& outputStream)
    : OutputStream(outputStream)
{ }

void XMLWriterASTVisitor::Visit(ModuleAST&)
{
    OutputStream << CurrentIndent << "<Module>\n";
    PushIndent();
}

void XMLWriterASTVisitor::Exit(ModuleAST&)
{
    PopIndent();
    OutputStream << CurrentIndent << "</Module>\n";
}

void XMLWriterASTVisitor::Visit(StatementAST&)
{
    OutputStream << CurrentIndent << "<Statement>\n";
    PushIndent();
}

void XMLWriterASTVisitor::Exit(StatementAST&)
{
    PopIndent();
    OutputStream << CurrentIndent << "</Statement>\n";
}

void XMLWriterASTVisitor::Visit(LocalDeclarationStatementAST&)
{
    OutputStream << CurrentIndent << "<LocalDeclaration>\n";
    PushIndent();
}

void XMLWriterASTVisitor::Exit(LocalDeclarationStatementAST&)
{
    PopIndent();
    OutputStream << CurrentIndent << "</LocalDeclaration>\n";
}

void XMLWriterASTVisitor::Visit(AssignmentStatementAST&)
{
    OutputStream << CurrentIndent << "<AssignmentStatement>\n";
    PushIndent();
}

void XMLWriterASTVisitor::Exit(AssignmentStatementAST&)
{
    PopIndent();
    OutputStream << CurrentIndent << "</AssignmentStatement>\n";
}

void XMLWriterASTVisitor::Visit(FactorAST&)
{
    OutputStream << CurrentIndent << "<Factor>\n";
    PushIndent();
}

void XMLWriterASTVisitor::Exit(FactorAST&)
{
    PopIndent();
    OutputStream << CurrentIndent << "</Factor>\n";
}

void XMLWriterASTVisitor::Visit(IdentifierFactorAST&)
{
    OutputStream << CurrentIndent << "<IdentifierFactor>\n";
    PushIndent();
}

void XMLWriterASTVisitor::Exit(IdentifierFactorAST&)
{
    PopIndent();
    OutputStream << CurrentIndent << "</IdentifierFactor>\n";
}

void XMLWriterASTVisitor::Visit(IntegerFactorAST&)
{
    OutputStream << CurrentIndent << "<IntegerFactor>\n";
    PushIndent();
}

void XMLWriterASTVisitor::Exit(IntegerFactorAST&)
{
    PopIndent();
    OutputStream << CurrentIndent << "</IntegerFactor>\n";
}

void XMLWriterASTVisitor::Visit(IdentifierAST& identifier)
{
    OutputStream << CurrentIndent << "<Identifier name=\"" << identifier.IdentifierName << "\"/>\n";
}

void XMLWriterASTVisitor::Exit(IdentifierAST&)
{
}

void XMLWriterASTVisitor::Visit(IntegerAST& integer)
{
    OutputStream << CurrentIndent << "<Integer value=\"" << integer.IntegerValue << "\"/>\n";
}

void XMLWriterASTVisitor::Exit(IntegerAST&)
{
}

void XMLWriterASTVisitor::PushIndent()
{
    CurrentIndent += "    ";
}

void XMLWriterASTVisitor::PopIndent()
{
    if (CurrentIndent.size() < 4)
    {
        throw std::logic_error("Indentation stack underflow");
    }

    CurrentIndent.resize(CurrentIndent.size() - 4);
}

#pragma once

#include <string>

#include <ast.hpp>

#include <Java/JavaBuilder.hpp>

std::string GetClassName(std::string input);

class Compiler {
public:
    explicit Compiler(std::string className);
    void Build(AstTree *tree);
    void Write();
protected:
    void BuildFunction(AstGlobalStatement *GS);
    void BuildStatement(AstStatement *stmt, JavaFunction *function);
private:
    std::string className;
    JavaClassBuilder *builder;
};

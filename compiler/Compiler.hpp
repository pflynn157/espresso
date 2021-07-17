#pragma once

#include <string>
#include <map>

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
    
    void BuildVarDec(AstStatement *stmt, JavaFunction *function);
    void BuildFuncCallStatement(AstStatement *stmt, JavaFunction *function);
    void BuildExpr(AstExpression *expr, JavaFunction *function);
    
    std::string GetTypeForExpr(AstExpression *expr);
private:
    std::string className;
    JavaClassBuilder *builder;
    
    int aCount = 1;
    std::map<std::string, int> objMap;
};

#include <cstdio>

#include <Compiler.hpp>

Compiler::Compiler(std::string className) {
    this->className = className;
    builder = new JavaClassBuilder(className);
    
    builder->ImportField("java/lang/System", "java/io/PrintStream", "out");
    builder->ImportMethod("java/io/PrintStream", "println", "(Ljava/lang/String;)V");
    builder->ImportMethod("java/io/PrintStream", "println", "(I)V");
}

void Compiler::Build(AstTree *tree) {
    // Build the functions
    for (auto GS : tree->getGlobalStatements()) {
        if (GS->getType() == AstType::Func) {
            BuildFunction(GS);
        }
    }
}

void Compiler::Write() {
    std::string fullName = className + ".class";
    
    FILE *file = fopen(fullName.c_str(), "wb");
    builder->Write(file);
    fclose(file);
}

// Builds a function
void Compiler::BuildFunction(AstGlobalStatement *GS) {
    AstFunction *func = static_cast<AstFunction *>(GS);
    
    JavaFunction *function = builder->CreateMethod(func->getName(), "([Ljava/lang/String;)V", F_PUBLIC | F_STATIC);
    
    for (AstStatement *stmt : func->getBlock()->getBlock()) {
        BuildStatement(stmt, function);
    }
}

// Builds a statement
void Compiler::BuildStatement(AstStatement *stmt, JavaFunction *function) {
    switch (stmt->getType()) {
        case AstType::FuncCallStmt: BuildFuncCallStatement(stmt, function); break;
    
        case AstType::Return: {
            if (stmt->getExpressionCount() == 0) {
                builder->CreateRetVoid(function);
            } else {
                // TODO
            }
        } break;
        
        default: {}
    }
}

// Builds a function call statement
void Compiler::BuildFuncCallStatement(AstStatement *stmt, JavaFunction *function) {
    AstFuncCallStmt *fc = static_cast<AstFuncCallStmt *>(stmt);
    
    if (fc->getName() == "println") {
        builder->CreateGetStatic(function, "out");
    }
    
    for (AstExpression *expr : fc->getExpressions()) {
        BuildExpr(expr, function);
    }
    
    builder->CreateInvokeVirtual(function, fc->getName());
}

// Builds an expression
void Compiler::BuildExpr(AstExpression *expr, JavaFunction *function) {
    switch (expr->getType()) {
        case AstType::StringL: {
            AstString *str = static_cast<AstString *>(expr);
            builder->CreateString(function, str->getValue());
        } break;
        
        default: {}
    }
}

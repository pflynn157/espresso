//
// Copyright 2021 Patrick Flynn
// This file is part of the Orka compiler.
// Orka is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <string>
#include <vector>

#include <ast/Types.hpp>

class AstStatement;

// Represents a function, external declaration, or global variable
class AstGlobalStatement {
public:
    explicit AstGlobalStatement() {}
    explicit AstGlobalStatement(AstType type) {
        this->type = type;
    }
    
    AstType getType() { return type; }
    
    virtual void print() {}
private:
    AstType type = AstType::EmptyAst;
};

// Represents a function
class AstFunction : public AstGlobalStatement {
public:
    explicit AstFunction(std::string name, bool routine = false, Attr attr = Attr::Public) 
             : AstGlobalStatement(AstType::Func) {
        this->name = name;
        this->routine = routine;
        this->attr = attr;
        block = new AstBlock;
    }
    
    std::string getName() { return name; }
    bool isRoutine() { return routine; }
    Attr getAttribute() { return attr; }
    DataType getDataType() { return dataType; }
    DataType getPtrType() { return ptrType; }
    std::vector<Var> getArguments() { return args; }
    AstBlock *getBlock() { return block; }
    
    void setArguments(std::vector<Var> args) { this->args = args; }
    
    void addStatement(AstStatement *statement) {
        block->addStatement(statement);
    }
    
    void setDataType(DataType dataType, DataType ptrType) {
        this->dataType = dataType;
        this->ptrType = ptrType;
    }
    
    void print() override;
private:
    std::string name = "";
    bool routine = false;
    Attr attr = Attr::Public;
    std::vector<Var> args;
    AstBlock *block;
    DataType dataType = DataType::Void;
    DataType ptrType = DataType::Void;
};


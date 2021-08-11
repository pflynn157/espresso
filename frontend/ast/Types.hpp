//
// Copyright 2021 Patrick Flynn
// This file is part of the Espresso compiler.
// Espresso is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <string>
#include <map>

enum class AstType {
    EmptyAst,
    Func,
    Return,
    
    FuncCallStmt,
    FuncCallExpr,
    
    VarDec,
    VarAssign,
    ArrayAssign,
    Sizeof,
    
    If,
    Elif,
    Else,
    While,
    Repeat,
    For,
    ForAll,
    End,
    
    Break,
    Continue,
    
    Neg,
    
    Add,
    Sub,
    Mul,
    Div,
    Rem,
    
    And,
    Or,
    Xor,
    Lsh,
    Rsh,
    
    EQ,
    NEQ,
    GT,
    LT,
    GTE,
    LTE,
    
    BoolL,
    CharL,
    ByteL,
    WordL,
    IntL,
    QWordL,
    StringL,
    ID,
    ArrayAccess
};

enum class DataType {
    Void,
    Bool,
    Char,
    Byte,
    UByte,
    Short,
    UShort,
    Int32,
    UInt32,
    Int64,
    UInt64,
    String,
    Array,
    Object
};

enum class Attr {
    Public,
    Protected,
    Private
};

struct Var {
    std::string name;
    DataType type;
    DataType subType;
};

// Represents an ENUM
class AstExpression;

struct EnumDec {
    std::string name;
    DataType type;
    std::map<std::string, AstExpression*> values;
};

// Represents a block
class AstStatement;

class AstBlock {
public:
    void addStatement(AstStatement *stmt) { block.push_back(stmt); }
    void addStatements(std::vector<AstStatement *> block) { this->block = block; }
    std::vector<AstStatement *> getBlock() { return block; }
private:
    std::vector<AstStatement *> block;
};

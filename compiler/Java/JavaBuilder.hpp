#pragma once

#include <string>
#include <arpa/inet.h>
#include <map>
#include <vector>

#include <Java/JavaIR.hpp>

struct Method {
    std::string name;
    std::string baseClass;
    int pos;

    Method(std::string name, int pos, std::string baseClass = "") {
        this->name = name;
        this->pos = pos;
        this->baseClass = baseClass;
    }
};

class JavaClassBuilder {
public:
    explicit JavaClassBuilder(std::string className);
    int AddUTF8(std::string value);
    int ImportClass(std::string baseClass);
    void ImportMethod(std::string baseClass, std::string name, std::string signature);
    void ImportField(std::string baseClass, std::string typeClass, std::string name);
    int FindMethod(std::string name, std::string baseClass);

    JavaFunction *CreateMethod(std::string name, std::string signature, int = F_PUBLIC);
    void CreateALoad(JavaFunction *func, int pos);
    void CreateAStore(JavaFunction *func, int pos);
    void CreateNew(JavaFunction *func, std::string name);
    void CreateDup(JavaFunction *func);
    void CreateGetStatic(JavaFunction *func, std::string name);
    void CreateString(JavaFunction *func, std::string value);
    void CreateInvokeSpecial(JavaFunction *func, std::string name, std::string baseClass = "");
    void CreateInvokeVirtual(JavaFunction *func, std::string name, std::string baseClass = "");
    void CreateInvokeStatic(JavaFunction *func, std::string name, std::string baseClass = "");
    void CreateRetVoid(JavaFunction *func);

    void Write(FILE *file);
private:
    JavaClassFile *java;
    std::string className;
    int codeIdx = 0;
    int superPos = 0;

    std::map<std::string, int> UTF8Index;
    std::map<std::string, int> classMap;
    std::map<std::string, int> fieldMap;
    //std::map<std::string, int> methodMap;
    std::vector<Method> methodMap;
    std::map<std::string, int> constMap;
};

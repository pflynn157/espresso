#include <Java/JavaBuilder.hpp>
#include <Java/JavaIR.hpp>

// Creates a static function
JavaFunction *JavaClassBuilder::CreateMethod(std::string name, std::string signature, int flags) {
    int nameIdx = AddUTF8(name);
    int sigIdx = AddUTF8(signature);

    JavaFunction *func = new JavaFunction(flags, nameIdx, sigIdx, codeIdx);
    java->methods.push_back(func);

    // Create a name and type entry
    JavaNameTypeEntry *nt = new JavaNameTypeEntry(nameIdx, sigIdx);
    int ntPos = java->AddConst(nt);

    // Create a method-ref entry
    JavaMethodRefEntry *method = new JavaMethodRefEntry(superPos, ntPos);
    int methodPos = java->AddConst(method);

    //methodMap[name] = methodPos;
    Method m(name, methodPos, className);
    methodMap.push_back(m);

    return func;
}

// Creates an ALOAD instruction
void JavaClassBuilder::CreateALoad(JavaFunction *func, int pos) {
    switch (pos) {
        case 0: func->addCode(JavaCode(0x2A)); break;
        case 1: func->addCode(JavaCode(0x2B)); break;
        case 2: func->addCode(JavaCode(0x2C)); break;
        case 3: func->addCode(JavaCode(0x2D)); break;

        default: {
            func->addCode(JavaCode(0x19, (unsigned char)pos));
        }
    }
}

// Creates an ASTORE instruction
void JavaClassBuilder::CreateAStore(JavaFunction *func, int pos) {
    switch (pos) {
        case 0: func->addCode(JavaCode(0x4B)); break;
        case 1: func->addCode(JavaCode(0x4C)); break;
        case 2: func->addCode(JavaCode(0x4D)); break;
        case 3: func->addCode(JavaCode(0x4E)); break;

        default: {
            func->addCode(JavaCode(0x3A, (unsigned char)pos));
        }
    }
}

// Creates a NEW instruction
void JavaClassBuilder::CreateNew(JavaFunction *func, std::string name) {
    int pos = classMap[name];

    JavaCode code(0xBB, (unsigned short)pos);
    func->addCode(code);
}

// Creates a DUP instruction
void JavaClassBuilder::CreateDup(JavaFunction *func) {
    func->addCode(JavaCode(0x59));
}

// Creates a getstatic instruction
void JavaClassBuilder::CreateGetStatic(JavaFunction *func, std::string name) {
    int fieldPos = fieldMap[name];

    JavaCode code(0xB2, (unsigned short)fieldPos);
    func->addCode(code);
}

// Creates a LDC instruction (loads a string specifically)
void JavaClassBuilder::CreateString(JavaFunction *func, std::string value) {
    int constPos = 0;

    if (constMap.find(value) == constMap.end()) {
        constPos = AddUTF8(value);
        JavaStringEntry *entry = new JavaStringEntry(constPos);
        constPos = java->AddConst(entry);

        constMap[value] = constPos;
    } else {
        constPos = constMap[value];
    }

    JavaCode code(0x12, (unsigned char)constPos);
    func->addCode(code);
}

// Creates an InvokeSpecial instruction
void JavaClassBuilder::CreateInvokeSpecial(JavaFunction *func, std::string name, std::string baseClass, std::string signature) {
    int methodPos = FindMethod(name, baseClass, signature);

    JavaCode code(0xB7, (unsigned short)methodPos);
    func->addCode(code);
}

// Creates an InvokeVirtual instruction
void JavaClassBuilder::CreateInvokeVirtual(JavaFunction *func, std::string name, std::string baseClass, std::string signature) {
    int methodPos = FindMethod(name, baseClass, signature);

    JavaCode code(0xB6, (unsigned short)methodPos);
    func->addCode(code);
}

// Creates an InvokeStatic instruction
void JavaClassBuilder::CreateInvokeStatic(JavaFunction *func, std::string name, std::string baseClass, std::string signature) {
    int methodPos = FindMethod(name, baseClass, signature);

    JavaCode code(0xB8, (unsigned short)methodPos);
    func->addCode(code);
}

// Creates a return-void call
void JavaClassBuilder::CreateRetVoid(JavaFunction *func) {
    func->addCode(JavaCode(0xB1));
}

// Creates a bipush call
void JavaClassBuilder::CreateBIPush(JavaFunction *func, int value) {
    JavaCode code(0x10, (unsigned char)value);
    func->addCode(code);
}

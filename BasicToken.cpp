#include "BasicToken.h"

#include <unordered_map>
#include <iostream>

std::string typeToString(const BasicTokenType type) {
    switch (type) {
        case BasicTokenType::EXPRESSION: return "EXPRESSION";
        case BasicTokenType::END: return "END";
        case BasicTokenType::GOTO: return "GOTO";
        case BasicTokenType::IDENTIFIER: return "IDENTIFIER";
        case BasicTokenType::IF: return "IF";
        case BasicTokenType::INPUT: return "INPUT";
        case BasicTokenType::LET: return "LET";
        case BasicTokenType::LINE_NUMBER: return "LINE_NUMBER";
        case BasicTokenType::PRINT: return "PRINT";
        case BasicTokenType::STRING: return "STRING";
        case BasicTokenType::THEN: return "THEN";
        default: return "UNKNOWN";
    }
}

BasicTokenType stringToType(const std::string& s) {
    const std::unordered_map<std::string, BasicTokenType> tokenMap = {
        {"EXPRESSION", BasicTokenType::EXPRESSION},
        {"END", BasicTokenType::END},
        {"GOTO", BasicTokenType::GOTO},
        {"IDENTIFIER", BasicTokenType::IDENTIFIER},
        {"IF", BasicTokenType::IF},
        {"INPUT", BasicTokenType::INPUT},
        {"LET", BasicTokenType::LET},
        {"LINE_NUMBER", BasicTokenType::LINE_NUMBER},
        {"PRINT", BasicTokenType::PRINT},
        {"STRING", BasicTokenType::STRING},
        {"THEN", BasicTokenType::THEN}
    };

    auto it = tokenMap.find(s);
    if (it != tokenMap.end()) {
        return it->second;
    }
    return BasicTokenType::UNKNOWN;
}

std::ostream &operator<<(std::ostream &os, const BasicToken &token) {
    os << typeToString(token.type);
    if (token.compareType(BasicTokenType::EXPRESSION) ||
        token.compareType(BasicTokenType::STRING) ||
        token.compareType(BasicTokenType::IDENTIFIER)) {
        os << "(" << token.expression << ")";
    }

    return os;
}

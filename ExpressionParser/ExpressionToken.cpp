#include "ExpressionToken.h"
#include<iostream>

std::string typeToString(ExpressionTokenType type) {
    switch (type) {
        case ExpressionTokenType::NUMBER: return "NUMBER";
        case ExpressionTokenType::ADD: return "ADD";
        case ExpressionTokenType::SUBTRACT: return "SUBTRACT";
        case ExpressionTokenType::MULTIPLY: return "MULTIPLY";
        case ExpressionTokenType::DIVIDE: return "DIVIDE";
        case ExpressionTokenType::LEFT_PAREN: return "LEFT PARENTHESES";
        case ExpressionTokenType::RIGHT_PAREN: return "RIGHT PARENTHESES";
        case ExpressionTokenType::FUNCTION: return "FUNCTION";
        default: return "UNKNOWN";
    }
}

std::ostream &operator<<(std::ostream &os, const ExpressionToken &token) {
    os << "TOKEN(" << typeToString(token.type);

    if (token.compareType(ExpressionTokenType::NUMBER)) {
        os << ", " << token.value;
    }
    if (token.compareType(ExpressionTokenType::FUNCTION)) {
        os << ", argCount = ";
        if (token.argCount <= 0) {
            os << "NOT SET";
        }
        else {
            os << token.argCount;
        }
    }

    os << ")";

    return os;
}

#pragma once

enum class ExpressionTokenType {
    NUMBER,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    LEFT_PAREN,
    RIGHT_PAREN,
    FUNCTION,
    COMMA,
    UNARY_MINUS,
    UNARY_PLUS,
    POWER
};
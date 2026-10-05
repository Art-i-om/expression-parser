#pragma once

enum class BasicTokenType {
    LINE_NUMBER,
    LET,
    PRINT,
    INPUT,
    IF,
    THEN,
    GOTO,
    END,

    IDENTIFIER,
    STRING,
    UNKNOWN,

    EXPRESSION
};
#pragma once
#include "BasicTokenType.h"
#include <string>
#include <utility>

std::string typeToString(BasicTokenType type);
BasicTokenType stringToType(const std::string& s);

class BasicToken {
private:
    BasicTokenType type;
    std::string expression;

public:
    explicit BasicToken(const BasicTokenType& t) : type(t) {}
    explicit BasicToken(std::string expr)
        : type(BasicTokenType::EXPRESSION), expression(std::move(expr)) {}
    BasicToken(const BasicTokenType& t, std::string  s) : type(t), expression(std::move(s)) {}

    friend std::ostream& operator<<(std::ostream& os, const BasicToken& token);

    [[nodiscard]] bool compareType(const BasicTokenType& other) const { return type == other; }
    [[nodiscard]] BasicTokenType getType() const { return type; }
    [[nodiscard]] std::string getExpression() const { return expression; }
};

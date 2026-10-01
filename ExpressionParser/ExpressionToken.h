#pragma once
#include "ExpressionTokenType.h"
#include <functional>
#include <vector>
#include <string>

#include "ExpressionParsError.h"

std::string typeToString(ExpressionTokenType type);

class ExpressionToken {
private:
    ExpressionTokenType type;
    double value;

    std::function<double(std::vector<double>)> func;
    int argCount = 0;

public:
    ExpressionToken(const ExpressionTokenType t, const double x) : type(t), value(x) {}
    explicit ExpressionToken(const double x) : type(ExpressionTokenType::NUMBER), value(x) {}
    explicit ExpressionToken(const ExpressionTokenType t) : type(t), value(0) {}
    explicit ExpressionToken(const std::function<double(std::vector<double>)>& f)
    : func(f), type(ExpressionTokenType::FUNCTION), value(0) {}

    friend std::ostream& operator<<(std::ostream& os, const ExpressionToken& token);

    [[nodiscard]] bool isNumber() const { return type == ExpressionTokenType::NUMBER; }
    [[nodiscard]] bool compareType(const ExpressionTokenType& other) const { return type == other; }
    [[nodiscard]] bool argsCountEmpty() const { return argCount <= 0; }
    [[nodiscard]] ExpressionTokenType getType() const { return type; }
    [[nodiscard]] double getValue() const { return value; }
    [[nodiscard]] int getArgsCount() const { return argCount; }
    [[nodiscard]] double applyFunction(const std::vector<double>& args) const {
        if (compareType(ExpressionTokenType::FUNCTION)) {
            return func(args);
        }

        throw ExpressionParsError("applyFunction() is only accessible for functions");
    }

    void setType(const ExpressionTokenType& t) {
        if (!compareType(ExpressionTokenType::NUMBER)) {
            type = t;
            return;
        }

        throw ExpressionParsError("Cannot change token type if it is already a number");
    }

    void setValue(const double& x) {
        if (compareType(ExpressionTokenType::NUMBER)) {
            value = x;
            return;
        }

        throw ExpressionParsError("setValue() only works with numbers");
    }
    void setArgCount(const int& cnt) {
        if (compareType(ExpressionTokenType::FUNCTION)) {
            argCount = cnt;
            return;
        }

        throw ExpressionParsError("setArgCount() only works with functions");
    }
    void decreaseArgsCount() { argCount--; }
};


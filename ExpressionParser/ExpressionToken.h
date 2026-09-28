#pragma once
#include "ExpressionTokenType.h"
#include <functional>
#include <vector>
#include <string>

class ExpressionToken {
private:
    ExpressionTokenType type;
    double value;
    std::function<double(std::vector<double>)> func;

public:
    ExpressionToken(const ExpressionTokenType t, const double x) : type(t), value(x) {}
    explicit ExpressionToken(const double x) : type(ExpressionTokenType::NUMBER), value(x) {}
    explicit ExpressionToken(const ExpressionTokenType t) : type(t), value(0) {}
    explicit ExpressionToken(const std::function<double(std::vector<double>)>& f)
    : func(f), type(ExpressionTokenType::FUNCTION), value(0) {}

    friend std::ostream& operator<<(std::ostream& os, const ExpressionToken& token);

    [[nodiscard]] bool isNumber() const { return type == ExpressionTokenType::NUMBER; }
    [[nodiscard]] bool compareType(const ExpressionTokenType& other) const { return type == other; }
    [[nodiscard]] ExpressionTokenType getType() const { return type; }
    [[nodiscard]] double getValue() const { return value; }

    void setValue(const double& x) { value = x; }
};


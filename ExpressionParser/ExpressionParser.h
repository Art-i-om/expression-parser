#pragma once

#include <deque>
#include <cmath>

#include "ExpressionToken.h"

class ExpressionParser {
private:
    std::deque<ExpressionToken> output;
    std::deque<ExpressionToken> operatorStack;
    std::vector<int> argsCount;

    std::vector<ExpressionToken> tokens;

    const std::unordered_map<std::string, std::function<double(std::vector<double>)>> funcs = {
        {"sin", [](const std::vector<double>& args) {
            return args.empty() ? 0.0 : std::sin(args[0]);
        } },
        {"cos", [](const std::vector<double>& args) {
            return args.empty() ? 0.0 : std::cos(args[0]);
        } },
        {"min", [](const std::vector<double>& args) {
            return args.empty() ? 0.0 : *std::min_element(args.begin(), args.end());
        } },
        {"max", [](const std::vector<double>& args) {
            return args.empty() ? 0.0 : *std::max_element(args.begin(), args.end());
        } }
    };
    const std::unordered_map<std::string, double> variables = {
        {"pi", std::numbers::pi_v<long double>},
        {"answer", 42},
        {"x", 1},
        {"y", 2},
        {"z", 3},
    };

    void flushToLeftParen();
    static int precedence(const ExpressionTokenType& type);
    static bool isRightAssociative(const ExpressionTokenType& type);

    void shuntingYardAlgorithm();
    double generateResult();

public:
    double evaluate(const std::string& expression);
};

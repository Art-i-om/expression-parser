#include "ExpressionParser.h"

#include "Lexer.h"

void ExpressionParser::flushToLeftParen() {
    while (!operatorStack.empty() &&
                !operatorStack.back().compareType(ExpressionTokenType::LEFT_PAREN))
        {
        output.push_back(operatorStack.back());
        operatorStack.pop_back();
                }
}

int ExpressionParser::precedence(const ExpressionTokenType& type) {
    switch (type) {
        case ExpressionTokenType::ADD:
        case ExpressionTokenType::SUBTRACT:
            return 1;
        case ExpressionTokenType::MULTIPLY:
        case ExpressionTokenType::DIVIDE:
            return 2;
        default:
            throw ExpressionParsError("There is no precedence for type " + typeToString(type));
    }
}

void ExpressionParser::shuntingYardAlgorithm() {
    bool expectOperand = true;

    for (const auto& token : tokens) {
        if (token.isNumber()) {
            if (!expectOperand) throw ExpressionParsError("unexpected number - missing operator?");
            output.push_back(token);
            expectOperand = false;
        }
        else if (token.compareType(ExpressionTokenType::FUNCTION)) {
            if (!expectOperand) throw ExpressionParsError("unexpected function call - missing operator?");
            operatorStack.push_back(token);
            argsCount.push_back(1);
        }
        else if (token.compareType(ExpressionTokenType::LEFT_PAREN)) {
            if (!expectOperand) throw ExpressionParsError("unexpected '(' - missing operator?");
            operatorStack.push_back(token);
        }
        else if (token.compareType(ExpressionTokenType::COMMA)) {
            if (expectOperand) throw ExpressionParsError("missing argument before ','");
            flushToLeftParen();
            if (operatorStack.size() < 2 ||
                !operatorStack[operatorStack.size() - 2].compareType(ExpressionTokenType::FUNCTION)) {
                throw ExpressionParsError("misplaced comma");
            }
            argsCount.back()++;
            expectOperand = true;
        }
        else if (token.compareType(ExpressionTokenType::RIGHT_PAREN)) {
            if (expectOperand) throw ExpressionParsError("missing operand before ')'");
            flushToLeftParen();
            if (operatorStack.empty()) throw ExpressionParsError("mismatched parentheses");
            operatorStack.pop_back();

            if (!operatorStack.empty() &&
                operatorStack.back().compareType(ExpressionTokenType::FUNCTION)) {
                ExpressionToken func = operatorStack.back();
                operatorStack.pop_back();
                func.setArgCount(argsCount.back());
                argsCount.pop_back();
                output.push_back(func);
            }

            expectOperand = false;
        }
        else {
            if (expectOperand) throw ExpressionParsError("unexpected operator - missing left operand?");

            while (!operatorStack.empty()) {
                const ExpressionToken& op = operatorStack.back();
                if (op.compareType(ExpressionTokenType::LEFT_PAREN) ||
                    precedence(token.getType()) > precedence(op.getType())) {
                    break;
                }

                output.push_back(op);
                operatorStack.pop_back();
            }
            operatorStack.push_back(token);
            expectOperand = true;
        }
    }

    if (expectOperand) throw ExpressionParsError("expression ends with a missing operand");

    while (!operatorStack.empty()) {
        output.push_back(operatorStack.back());
        operatorStack.pop_back();
    }
}

double ExpressionParser::generateResult() {
    std::deque<ExpressionToken> result;
    while (!output.empty()) {
        auto elem = output.front();
        output.pop_front();
        if (elem.isNumber()) {
            result.push_back(elem);
        }
        else if (elem.compareType(ExpressionTokenType::FUNCTION)) {
            const size_t n = elem.getArgsCount();
            if (result.size() < n) throw ExpressionParsError("not enough arguments for function call");

            std::vector<double> args;
            args.reserve(n);
            for (size_t i = result.size() - n; i < result.size(); i++) {
                args.push_back(result[i].getValue());
            }
            result.erase(result.end() - n, result.end());

            double funcResult = elem.applyFunction(args);
            auto resultToken = ExpressionToken(funcResult);
            result.push_back(resultToken);
        }
        else {
            if (result.size() < 2) throw ExpressionParsError("missing operand");
            auto right = result.back(); result.pop_back();
            auto left = result.back(); result.pop_back();

            auto resultToken = ExpressionToken(ExpressionTokenType::NUMBER);

            switch (elem.getType()) {
                case ExpressionTokenType::ADD:
                    resultToken.setValue(left.getValue() + right.getValue());
                    break;
                case ExpressionTokenType::SUBTRACT:
                    resultToken.setValue(left.getValue() - right.getValue());
                    break;
                case ExpressionTokenType::MULTIPLY:
                    resultToken.setValue(left.getValue() * right.getValue());
                    break;
                case ExpressionTokenType::DIVIDE:
                    resultToken.setValue(left.getValue() / right.getValue());
                    break;
                default:
                    throw ExpressionParsError("Invalid expression token type for binary operations");
            }

            result.push_back(resultToken);
        }
    }

    if (result.size() != 1) throw ExpressionParsError("malformed expression");
    return result.back().getValue();
}

double ExpressionParser::evaluate(const std::string &expression) {
    Lexer::tokenize(expression, funcs, variables, tokens);

    shuntingYardAlgorithm();

    const double result = generateResult();
    return result;
}

#include "Lexer.h"
#include "ExpressionToken.h"
#include "LexError.h"

#include <charconv>
#include <functional>
#include <iostream>
#include <map>

double Lexer::getNumber(const std::string &expression, long long &index) {
    double val = 0;

    auto [ptr, ec] = std::from_chars(
        expression.data() + index,
        expression.data() + expression.size(),
        val
        );

    if (ec == std::errc{}) {
        index = ptr - expression.data() - 1;
        return val;
    }

    std::cerr << "ERROR: Failed to convert string into number" << std::endl;
    std::exit(-1);
}

std::string Lexer::getWord(const std::string &expression, long long &index) {
    std::string word;
    long long i = index;

    for (char c = expression[i]; isalpha(c); i++, c = expression[i]) {
        word += c;
    }

    if (word.empty()) {
        std::cerr << "ERROR: Failed to get word from expression" << std::endl;
        std::exit(-1);
    }

    index = i - 1;
    return word;
}

void Lexer::tokenize(const std::string& expression,
                     const std::unordered_map<std::string, std::function<double(std::vector<double>)>>& funcs,
                     const std::unordered_map<std::string, double>& variables,
                     std::vector<ExpressionToken>& tokens) {
    tokens.clear();
    const auto n = static_cast<long long>(expression.size());

    std::pair<int, int> count_parentheses_pairs;

    for (long long i = 0; i < n; i++) {
        const char symbol = expression[i];
        if (symbol == ' ') continue;

        switch (symbol) {
            case '+': tokens.emplace_back(ExpressionTokenType::ADD); break;
            case '-': tokens.emplace_back(ExpressionTokenType::SUBTRACT); break;
            case '*': tokens.emplace_back(ExpressionTokenType::MULTIPLY); break;
            case '/': tokens.emplace_back(ExpressionTokenType::DIVIDE); break;
            case '(': count_parentheses_pairs.first++;
                tokens.emplace_back(ExpressionTokenType::LEFT_PAREN); break;
            case ',': tokens.emplace_back(ExpressionTokenType::COMMA); break;

            case ')':
                count_parentheses_pairs.second++;
                skipSpaces(expression, i);
                tokens.emplace_back(ExpressionTokenType::RIGHT_PAREN);

                if (i + 1 < n) {
                    const char next = expression[i + 1];
                    if (next == '(' || isalpha(static_cast<unsigned char>(next)) ||
                        isdigit(static_cast<unsigned char>(next))) {
                        tokens.emplace_back(ExpressionTokenType::MULTIPLY);
                    }
                }
                break;

            default:
                if (isdigit(symbol)) {
                    double val = getNumber(expression, i);
                    tokens.emplace_back(val);

                    skipSpaces(expression, i);
                    if (i + 1 < n) {
                        const char next = expression[i + 1];
                        if (isalpha(static_cast<unsigned char>(next)) || next == '(') {
                            tokens.emplace_back(ExpressionTokenType::MULTIPLY);
                        }
                        else if (isdigit(static_cast<unsigned char>(next))) {
                            throw LexError("ERROR: unexpected second number after " +
                                std::to_string(val) + " - missing operator?");
                        }
                    }
                    break;
                }

                if (isalpha(symbol)) {
                    std::string word = getWord(expression,i);
                    skipSpaces(expression, i);

                    const bool hasNext = i + 1 < n;
                    const char next = hasNext ? expression[i + 1] : '\0';

                    if (hasNext && next == '(' && funcs.contains(word)) {
                        tokens.emplace_back(funcs.at(word));
                        break;
                    }

                    if (variables.contains(word)) {
                        tokens.emplace_back(variables.at(word));
                        if (hasNext && next == '(') {
                            tokens.emplace_back(ExpressionTokenType::MULTIPLY);
                        }
                        break;
                    }

                    if (hasNext && next == '(') {
                        throw LexError("ERROR: no such function called '" + word + "'");
                    }
                    throw LexError("ERROR: no such variable called '" + word + "'");
                }

                throw LexError(std::string("unknown symbol '") + symbol + "' in expression");
        }
    }

    if (count_parentheses_pairs.first != count_parentheses_pairs.second) {
        throw LexError("There are missing parentheses");
    }
}

void Lexer::printTokens(const std::vector<ExpressionToken> &tokens) {
    for (const auto& token : tokens) {
        std::cout << token << "\n";
    }
}

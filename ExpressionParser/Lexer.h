#pragma once

#include <vector>
#include <string>
#include <map>
#include <functional>

#include "ExpressionToken.h"
#include "LexError.h"

class Lexer {
private:
    static void skipSpaces(const std::string& expr, long long& i) {
        while (i + 1 < static_cast<long long>(expr.size()) && expr[i + 1] == ' ') {
            i++;
        }
    }

public:
    static void tokenize(const std::string& expression,
        const std::map<std::string, std::function<double(std::vector<double>)>>& funcs,
        const std::map<std::string, double>& variables,
        std::vector<ExpressionToken>& tokens
        );

    static double getNumber(const std::string& expression, long long& index);
    static std::string getWord(const std::string& expression, long long& index);
};

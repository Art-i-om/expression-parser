#pragma once

#include <string>
#include <vector>

#include "BasicToken.h"

class BasicLexer {
private:
    static double getNumber(const std::string& expression, long long& index);
    static std::string getWord(const std::string& expression, long long& index);
    static std::string getString(const std::string& expression, long long& index);

    static char getSpecialLetter(const char& c);

public:
    static void tokenizeLine(const std::string& line, std::vector<BasicToken>& tokens);

    static void printTokens(const std::vector<BasicToken>& tokens);
};

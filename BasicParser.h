#pragma once
#include <vector>

#include "BasicParsError.h"
#include "BasicToken.h"
#include "ExpressionParser/ExpressionParser.h"

class BasicParser {
private:
    std::vector<BasicToken> tokens;
    size_t currentIndex = 0;

    ExpressionParser parser;

    void parseLet();
    void parsePrint();
    void parseInput();
    void parseIf();
    void parseGoto();
    void parseEnd();

    [[nodiscard]] const BasicToken& current() const;
    BasicToken& advance();

    bool check(BasicTokenType type) const;
    BasicToken expect(BasicTokenType type);

    static void error(const std::string& message) {
        throw BasicParsError(message);
    };

public:
    void parseLine(const std::vector<BasicToken>& t);
};

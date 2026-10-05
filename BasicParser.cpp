#include "BasicParser.h"
#include "BasicParsError.h"
#include <iostream>

const BasicToken& BasicParser::current() const {
    if (currentIndex >= tokens.size()) {
        throw BasicParsError("Unexpected end of input");
    }

    return tokens[currentIndex];
}

BasicToken &BasicParser::advance() {
    if (currentIndex >= tokens.size()) {
        throw BasicParsError("Unexpected end of input");
    }

    return tokens[currentIndex++];
}

bool BasicParser::check(BasicTokenType type) const {
    return current().compareType(type);
}

BasicToken BasicParser::expect(BasicTokenType type) {
    if (!check(type)) {
        error("Unexpected token");
    }

    return advance();
}

void BasicParser::parsePrint() {
    advance();

    if (check(BasicTokenType::STRING)) {
        auto str = advance();
        std::cout << str.getExpression();
    }
    else if (check(BasicTokenType::EXPRESSION)) {
        auto token = advance();
        double result = parser.evaluate(token.getExpression());

        std::cout << result;
    }
    else {
        error("Expected string or expression after PRINT");
    }
}

void BasicParser::parseLet() {

}

void BasicParser::parseEnd() {

}

void BasicParser::parseGoto() {

}

void BasicParser::parseIf() {

}

void BasicParser::parseInput() {

}

void BasicParser::parseLine(const std::vector<BasicToken> &t) {
    tokens = t;
    currentIndex = 0;

    switch (current().getType()) {
        case BasicTokenType::LET:
            parseLet();
            break;
        case BasicTokenType::PRINT:
            parsePrint();
            break;

        default:
            error("Expected a statement");
    }
}

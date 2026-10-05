#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "BasicLexer.h"
#include "BasicToken.h"

inline void BasicLexerTokenizerTests(const std::string& line,
    std::vector<BasicToken>& tokens) {
    try {
        BasicLexer::tokenizeLine(line, tokens);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "ERROR: " + std::string(e.what());
    }
}
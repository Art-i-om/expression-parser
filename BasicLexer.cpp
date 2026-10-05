#include "BasicLexer.h"
#include "BasicToken.h"

#include <charconv>
#include <iostream>
#include <set>

#include "BasicLexError.h"

std::string BasicLexer::getWord(const std::string &expression, long long &index) {
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

char BasicLexer::getSpecialLetter(const char &c) {
    switch (c) {
        case 'n': return '\n';
        case 't': return '\t';
        case 'v': return '\v';
        case 'b': return '\b';
        case 'r': return '\r';
        case 'f': return '\f';
        case 'a': return '\a';
        case '0': return '\0';
        case '\\': return '\\';
        case '\'': return '\'';
        case '\"': return '\"';
        case '\?': return '\?';
        default: throw BasicLexError("No such special character");
    }
}

std::string BasicLexer::getString(const std::string &expression, long long &index) {
    std::string str;
    if (index + 1 >= expression.length()) {
        throw BasicLexError("Unexpected symbol '\"'");
    }
    long long i = index + 1;

    bool special_letter = false;
    for (char c = expression[i]; i < expression.length(); i++, c = expression[i]) {
        if (special_letter) {
            str += getSpecialLetter(c);
            special_letter = false;
            continue;
        }

        if (c == '\\') {
            special_letter = true;
            continue;
        }

        if (c == '\"') {
            break;
        }

        str += c;
    }

    index = i;
    return str;
}

double BasicLexer::getNumber(const std::string &expression, long long &index) {
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

// line is smth like: "PRINT 1" where \n states for end of line
void BasicLexer::tokenizeLine(const std::string &line, std::vector<BasicToken> &tokens) {
    tokens.clear();
    const auto n = static_cast<long long>(line.size());

    bool is_line_number = true;

    for (long long i = 0; i < n; i++) {
        if (line[i] == ' ') continue;

        if (line[i] == '"') {
            std::string str = getString(line, i);
            tokens.emplace_back(BasicTokenType::STRING, str);
            continue;
        }

        const std::string word = getWord(line, i);

        switch (const BasicTokenType type = stringToType(word)) {
            case BasicTokenType::PRINT:
                tokens.emplace_back(type);
                break;
            case BasicTokenType::LET:
                tokens.emplace_back(type);
                break;
            case BasicTokenType::THEN:
                tokens.emplace_back(type);
                break;
            case BasicTokenType::END:
                tokens.emplace_back(type);
                break;
            case BasicTokenType::GOTO:
                tokens.emplace_back(type);
                break;
            case BasicTokenType::IDENTIFIER:
                tokens.emplace_back(type);
                break;
            case BasicTokenType::IF:
                tokens.emplace_back(type);
                break;
            case BasicTokenType::INPUT:
                tokens.emplace_back(type);
                break;
            default:
                throw BasicLexError("Unknown word " + word);
        }
    }
}

void BasicLexer::printTokens(const std::vector<BasicToken> &tokens) {
    for (const auto& token : tokens) {
        std::cout << token << "\n";
    }
}

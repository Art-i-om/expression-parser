#include "Tests.h"
#include <fstream>
#include <deque>
#include <fstream>

#include "BasicParser.h"

int main() {
    // Create tokenizer for BASIC interpreter
    // Be able to read line by line and execute them

#if 1
    std::ifstream file("../TestExpressions.txt");

    if (!file.is_open()) {
        std::cerr << "ERROR: cannot open file!" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<BasicToken> tokens;

    auto basic = BasicParser();
    while (std::getline(file, line)) {
        BasicLexer::tokenizeLine(line, tokens);

        basic.parseLine(tokens);
    }

    file.close();
#endif
}

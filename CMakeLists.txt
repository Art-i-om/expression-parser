cmake_minimum_required(VERSION 4.2)
project(IntepreterBASIC)

set(CMAKE_CXX_STANDARD 23)

add_executable(IntepreterBASIC main.cpp
        ExpressionParser/ExpressionTokenType.h
        ExpressionParser/Lexer.cpp
        ExpressionParser/Lexer.h
        Tests.h
        ExpressionParser/ExpressionToken.cpp
        ExpressionParser/ExpressionToken.h
        ExpressionParser/LexError.h
        ExpressionParser/ExpressionParser.cpp
        ExpressionParser/ExpressionParser.h
        ExpressionParser/ExpressionParsError.h
        BasicTokenType.h
        BasicToken.cpp
        BasicToken.h
        BasicLexer.cpp
        BasicLexer.h
        BasicLexError.h
        BasicParser.cpp
        BasicParser.h
        BasicParsError.h
)

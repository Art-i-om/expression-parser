#pragma once
#include <stdexcept>

class BasicLexError : std::runtime_error {
    using std::runtime_error::runtime_error;
};
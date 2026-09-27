#pragma once
#include <stdexcept>

struct LexError : std::runtime_error {
    using std::runtime_error::runtime_error;
};

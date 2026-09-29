#pragma once
#include <stdexcept>

struct ExpressionParsError : std::runtime_error {
    using std::runtime_error::runtime_error;
};

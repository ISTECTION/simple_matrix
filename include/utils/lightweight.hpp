#ifndef _LIGHTWEIGHT_HPP
#define _LIGHTWEIGHT_HPP
#include <cmath>            /// sqrt

namespace utils {

    #if defined(__cpp_generic_lambdas) && __cpp_generic_lambdas >= 201707L
    constexpr auto EQUAL = [] <typename T> (T a, T b) { return (abs(a - b) < 1E-8); };
    #elif defined(__cpp_constexpr) && __cpp_constexpr >= 201603L
    constexpr auto EQUAL = [](auto a, auto b) { return (abs(a - b) < 1E-8); };
    #else
    auto EQUAL = [](auto a, auto b) { return (abs(a - b) < 1E-8); };
    #endif

}

#endif /// _LIGHTWEIGHT_HPP
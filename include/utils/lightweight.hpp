#ifndef _LIGHTWEIGHT_HPP
#define _LIGHTWEIGHT_HPP
#include <cmath>            /// abs sqrt

namespace utils {
    constexpr auto EQUAL = []<typename T>(T a, T b) -> bool { return (abs(a - b) < 1E-8); };

    // #if   defined(__cpp_generic_lambdas) && __cpp_generic_lambdas >= 201707L     # typename
    // #elif defined(__cpp_constexpr)       && __cpp_constexpr       >= 201603L     # constexpr
}

#endif /// _LIGHTWEIGHT_HPP
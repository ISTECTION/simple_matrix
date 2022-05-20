#ifndef _LIGHTWEIGHT_HPP
#define _LIGHTWEIGHT_HPP
#include <cmath>            /// sqrt

namespace utils {

    auto EQUAL = []<typename T>(T a, T b) { return (abs(a - b) < 1E-8); };

}

#endif /// _LIGHTWEIGHT_HPP
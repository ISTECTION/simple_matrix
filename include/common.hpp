#ifndef _COMMON_HPP
#define _COMMON_HPP
#include <iostream>     /// std::is_integral & std::is_floating_point

template <typename T>
concept _Vec_Type = std::is_integral<T>::value or std::is_floating_point<T>::value;

template <typename T> concept _Matrix_Type = _Vec_Type<T>;

#endif /// _COMMON_HPP
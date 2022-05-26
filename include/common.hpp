#ifndef _COMMON_HPP
#define _COMMON_HPP
#include <filesystem>   /// std::filesystem::path
#include <iostream>     /// std::is_integral_v & std::is_floating_point_v

template <typename T>
concept _Vec_Type =
    std::is_integral_v<T> or
    std::is_floating_point_v<T>;

template <typename T>
concept _Matrix_Type = _Vec_Type<T>;

template <typename T>
concept _Read_type =
    std::is_same_v<T, std::string> or
    std::is_same_v<T, std::filesystem::path>;

#endif /// _COMMON_HPP
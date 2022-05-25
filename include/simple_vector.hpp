#pragma once
#ifndef _SIMPLE_VECTOR_HPP
#define _SIMPLE_VECTOR_HPP
#include "exception/exception.hpp"
#include "utils/lightweight.hpp"
#include "common.hpp"

#include <iostream>         /// std::cout
#include <numeric>          /// std::inner_product
#include <sstream>          /// std::ostringstream
#include <iomanip>          /// std::setw
#include <string>           /// std::string
#include <vector>           /// std::vector

/// ----------------- C headers ----------------- ///
#include <windows.h>        /// SetConsoleOutputCP()
/// ----------------- C headers ----------------- ///

namespace simple {

    template <_Vec_Type T>
    class vector final : public std::vector<T>
    {
    private:
        using ::std::vector<T>::vector;
    public:
        constexpr vector (const std::vector<T>& _v) noexcept
            : std::vector<T>::vector(_v) { }

        constexpr auto norm () const noexcept;

        std::string pretty () const noexcept;
    };

    template <_Vec_Type T>
    constexpr auto vector<T>::norm () const noexcept {
        return sqrt(
            std::inner_product(
                this->begin(), this->end(), this->begin(), 0)
        );
    }

    template <_Vec_Type T>
    std::string vector<T>::pretty () const noexcept {
        if (this->size() == 0) { return std::string { "empty" }; }

        std::ostringstream osstr, main;
        std::vector<std::string> strs;
        size_t mwidth = 0;
        std::size_t _count = this->size();

        for (size_t i = 0; i < _count; ++i) {
            double term = (*this)[i];
            osstr << (utils::EQUAL( term, 0.0 ) ? 0 : term);
            std::string str = osstr.str();
            osstr.str(std::string { });
            strs.push_back(str);
            std::size_t nl = str.size();
            mwidth = nl > mwidth ? nl : mwidth;
        }
        size_t midwidth = (mwidth * _count) + ((_count + 1) << 1);
        main << "┌─" << std::setw(midwidth - 2) << "" << "─┐";
        main << '\n' << "│";
        for (size_t i = 0; i < _count; i++) {
            std::string str = strs[i];
            int wlen = (str.size() + mwidth + 1) >> 1;
            main << "  " << std::setw(wlen) << str
                << std::setw(mwidth - wlen) << "";
        }
        main << "  │";
        main << '\n' << "└─" << std::setw(midwidth - 2) << "" << "─┘";

        SetConsoleOutputCP(CP_UTF8);
        return main.str();
    }
}

#endif /// _SIMPLE_VECTOR_HPP
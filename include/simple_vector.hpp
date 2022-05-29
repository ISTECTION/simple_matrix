#pragma once
#ifndef _SIMPLE_VECTOR_HPP
#define _SIMPLE_VECTOR_HPP
#include "exception/exception.hpp"
#include "utils/lightweight.hpp"
#include "common.hpp"

#include <algorithm>
#include <iterator>

#include <unordered_map>    /// std::unordered_map
#include <iostream>         /// std::cout
#include <numeric>          /// std::inner_product
#include <sstream>          /// std::ostringstream
#include <iomanip>          /// std::setw
#include <fstream>          /// std::ifstream
#include <string>           /// std::string
#include <vector>           /// std::vector

/// ----------------- C headers ----------------- ///
#include <windows.h>        /// SetConsoleOutputCP()
/// ----------------- C headers ----------------- ///

enum class SEPARATOR { WHITESPACE, NEW_LINE };

namespace simple {

    template <_Vec_Type T>
    class vector final : public std::vector<T>
    {
    private:
        using ::std::vector<T>::vector;
    public:
        constexpr vector (const std::vector<T>& _v) noexcept
            : std::vector<T>::vector(_v) { }

        [[nodiscard]] constexpr auto norm () const noexcept;

        std::string pretty () const noexcept;
    };

    template <_Vec_Type T>
    constexpr auto vector<T>::norm () const noexcept {
        return sqrt(
            std::inner_product(
                this->begin(), this->end(), this->begin(), 0.0)
        );
    }

    template <_Vec_Type T>
    std::string vector<T>::pretty () const noexcept {
        if (this->size() == 0) { return std::string { "empty" }; }
        if constexpr (std::is_integral<T>::value or std::is_floating_point<T>::value) {
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

        } else {
            return
            std::string { "I can't process this type" };
        }
    }

    template <_File_type T, _Vec_Type U>
    void read (vector<U>& _vec, T _path) {

        std::ifstream i_file(_path);
        if (i_file.is_open()) {
            _vec.clear();
            std::copy(
                std::istream_iterator<U>(i_file),
                std::istream_iterator<U>(),
                std::back_inserter(_vec));
            i_file.close();
        } else {
            using enum ::exception::TYPE;
            throw exception(FILE_OPENING_ERROR);
        }
    }

    template <_File_type T, _Vec_Type U>
    void read (vector<U>& _vec, T _path, std::size_t _count) {

        std::ifstream i_file(_path);
        if (i_file.is_open()) {
            _vec.resize(_count);

            std::size_t _Count = 0;
            while (_Count < _count && i_file >> _vec[_Count]) { _Count++; }
            if (_Count != _count) {
                using enum ::exception::TYPE;
                throw exception(LITTLE_DATA_ERROR);
            }
            i_file.close();
        } else {
            using enum ::exception::TYPE;
            throw exception(FILE_OPENING_ERROR);
        }
    }

    template <_File_type T, _Vec_Type U>
    void write (const vector<U>& _vec, T _path, SEPARATOR _sep = SEPARATOR::WHITESPACE) {
        std::unordered_map<SEPARATOR, std::string> _separator_map_write_file = {
            { SEPARATOR::WHITESPACE, " "  },
            { SEPARATOR::NEW_LINE,   "\n" },
        };

        std::ofstream o_file(_path);
        if (o_file.is_open()) {
            std::string _separator = _separator_map_write_file.at(_sep);
            std::ostream_iterator<U> output_it(o_file, _separator.c_str());
            std::copy(_vec.begin(), _vec.end(), output_it);
            o_file.close();
        } else {
            using enum ::exception::TYPE;
            throw exception(FILE_OPENING_ERROR);
        }
    }

    template <_Vec_Type T>
    std::ostream& operator<< (std::ostream& out, const vector<T>& _vec) { return out << _vec.pretty(); }
}

#endif /// _SIMPLE_VECTOR_HPP
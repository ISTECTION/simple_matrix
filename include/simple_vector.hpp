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
#include <ranges>

#include <windows.h>

/** @enum  SEPARATOR
  * @brief Перечисление с выбором разделителя при записи файла
  * @var   SEPARATOR::WHITESPACE
  * Все элементы вектора будут напечатаны через пробел
  * @var   SEPARATOR::NEW_LINE
  * Каждый элемент вектора будет напечатан с новой строки
  */
enum class SEPARATOR { WHITESPACE, NEW_LINE };

namespace simple {

    /** @class simple::vector
      * @brief Простой векторный класс
      * @details В данном классе реализованы функции
      * вычисления нормы вектора и демонстрации его
      * в виде красиво отформатированной строки
      * @tparam T Любые целочисленные и вещественные типы
      */
    template <_Vec_Type T>
    class vector final : public std::vector<T>
    {
    private:
        using ::std::vector<T>::vector;
    public:
        constexpr vector (const std::vector<T>& _v) noexcept
            : std::vector<T>::vector(_v) { }

        /** @fn constexpr auto norm () const noexcept
          * @brief Вычисляет норму вектора
          * @return Норму вектора
          */
        [[nodiscard]] constexpr auto norm () const noexcept;

        /** @addtogroup pretty
          * Функции генерации красивых матриц и векторов
          * @{
          */
        std::string pretty () const noexcept;
        /** @} */
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

            for (size_t i : std::views::iota(0ull, _count)) {
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
            for (size_t i : std::views::iota(0ull, _count)) {
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

    /** @fn void read (vector<U>& _vec, T _path)
      * @brief  Чтение вектора из файла неизвестного размера
      * @tparam U Любые целочисленные и вещественные типы
      * @tparam T std::filesystem::path || std::string
      * @param[out] _vec  Вектор в который будут записаны данные
      * @param[in]  _path Путь до файла
      * @exception exception::TYPE::FILE_OPENING_ERROR В случае неудачи при открытии файла
      */
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

    /** @fn void read (vector<U>& _vec, T _path, std::size_t _count)
      * @brief  Чтение вектора из файла известного размера
      * @tparam U Любые целочисленные и вещественные типы
      * @tparam T std::filesystem::path || std::string
      * @param[out] _vec   Вектор в который будут записаны данные
      * @param[in]  _path  Путь до файла
      * @param[in]  _count Количество елементов
      * @exception exception::TYPE::LITTLE_DATA_ERROR  В случае невозможности считать данное количестов элементов из файла
      * @exception exception::TYPE::FILE_OPENING_ERROR В случае неудачи при открытии файла
      */
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

    /** @fn void write (const vector<U>& _vec, T _path, SEPARATOR _sep = SEPARATOR::WHITESPACE)
      * @brief  Запись вектора в файл
      * @tparam U Любые целочисленные и вещественные типы
      * @tparam T std::filesystem::path || std::string
      * @param _vec  Сохраняемый в файл вектор
      * @param _path Путь к файлу
      * @param _sep  Разделитель между елементами в выходном файле
      * @exception exception::TYPE::FILE_OPENING_ERROR В случае неудачи при открытии файла
      */
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
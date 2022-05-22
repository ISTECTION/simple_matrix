#pragma once
#ifndef _SIMPLE_MATRIX_HPP
#define _SIMPLE_MATRIX_HPP
#include "exception/exception.hpp"
#include "utils/lightweight.hpp"
#include "simple_vector.hpp"

namespace simple {

    template <class T>
    class matrix final : public std::vector<std::vector<T>>
    {
    private:
        using ::std::vector<std::vector<T>>::vector;
    public:
        std::size_t size_rows     () const noexcept { return this->size(); }
        std::size_t size_collumns () const noexcept { return this->empty() ? 0 : this->cbegin()->size(); }

        simple::vector<T> get_row (std::size_t _row) const {
            return simple::vector<T>(this->at(_row));
        }

        simple::vector<T> get_collumn (std::size_t _col) const {
            if (_col >= size_collumns()) {
                using enum ::exception::TYPE;
                throw exception(INDEX_COLLUMN_ERROR);
            }
            simple::vector<T> _col_v(this->size());
            for (size_t i = 0; i < this->size(); i++)
                _col_v[i] = (*this)[i][_col];
            return _col_v;
        }

        void set_row (std::size_t _row, const simple::vector<T>& _row_v) {
            if (_row >= size_rows()) {
                using enum ::exception::TYPE;
                throw exception(INDEX_ROW_ERROR);
            }
            (*this)[_row] = _row_v;
        }

        void set_collumn (std::size_t _col, const simple::vector<T>& _col_v) {
            if (_col >= size_collumns()) {
                using enum ::exception::TYPE;
                throw exception(INDEX_COLLUMN_ERROR);
            }
            for (size_t i = 0; i < this->size(); i++)
                (*this)[i][_col] = _col_v[i];
        }

        std::string pretty () const noexcept {
            std::size_t size_rows     = this->size_rows();
            std::size_t size_collumns = this->size_collumns();

            if (size_rows == 0 || size_collumns == 0) { return std::string { "empty" }; }

            std::ostringstream osstr, main;
            std::vector<std::string> strs;
            std::size_t mwidth = 0;

            for (size_t i = 0; i < size_rows; ++i) {
                for (size_t j = 0; j < size_collumns; ++j) {
                    double term = (*this)[i][j];
                    osstr << (utils::EQUAL( term, 0.0 ) ? 0 : term);
                    std::string str = osstr.str();
                    osstr.str(std::string { });
                    strs.push_back(str);
                    std::size_t nl = str.size();
                    mwidth = nl > mwidth ? nl : mwidth;
                }
            }

            std::size_t midwidth = (mwidth * size_rows) + ((size_rows + 1) << 1);
            main << "┌─" << std::setw(midwidth - 2) << "" << "─┐";
            for (size_t i = 0; i < size_rows; i++) {
                main << '\n' << "│";
                for (size_t j = 0; j < size_collumns; j++) {
                    std::string str = strs[i * size_collumns + j];
                    int wlen = (str.size() + mwidth + 1) >> 1;
                    main << "  " << std::setw(wlen) << str
                        << std::setw(mwidth - wlen) << "";
                }
                main << "  │";
            }
            main << '\n' << "└─" << std::setw(midwidth - 2) << "" << "─┘";

            SetConsoleOutputCP(CP_UTF8);
            return main.str();
        }

        matrix<T>& operator+= (const matrix<T>& A) {
            std::size_t _sr = size_rows();
            std::size_t _sc = size_collumns();

            if (_sr != A.size_rows() || _sc != A.size_collumns()) {
                using enum ::exception::TYPE;
                throw exception(INCOMPATIBLE_SIZE_ERROR);
            }

            for (size_t i = 0; i < _sr; i++)
            for (size_t j = 0; j < _sc; j++)
                (*this)[i][j] += A[i][j];
            return *this;
        }

        matrix<T>& operator-= (const matrix<T>& A) {
            std::size_t _sr = size_rows();
            std::size_t _sc = size_collumns();

            if (_sr != A.size_rows() || _sc != A.size_collumns()) {
                using enum ::exception::TYPE;
                throw exception(INCOMPATIBLE_SIZE_ERROR);
            }

            for (size_t i = 0; i < _sr; i++)
            for (size_t j = 0; j < _sc; j++)
                (*this)[i][j] -= A[i][j];
            return *this;
        }

        matrix<T>& operator*= (double _koef) {
            std::size_t _sizecollumn = size_collumns();
            for (size_t i = 0; i < this->size(); i++)
            for (size_t j = 0; j < _sizecollumn; j++)
                (*this)[i][j] *= _koef;
            return *this;
        }

        matrix<T>& operator/= (double _koef) {
            std::size_t _sizecollumn = size_collumns();
            for (size_t i = 0; i < this->size(); i++)
            for (size_t j = 0; j < _sizecollumn; j++)
                (*this)[i][j] /= _koef;
            return *this;
        }

        matrix<T>& operator*= (const matrix<T>& B) {
            if (size_collumns() != B.size_rows()) {
                using enum ::exception::TYPE;
                throw exception(INCOMPATIBLE_SIZE_ERROR);
            }
            std::size_t _Asr = size_rows();
            std::size_t _Bsc = B.size_collumns();

            for (size_t i = 0; i < _Asr; i++) {

                simple::vector<T> _row(_Bsc);
                for (size_t j = 0; j < _Bsc; j++) {
                    T _sum = 0;
                    for (size_t k = 0; k < size_collumns(); k++)
                        _sum += (*this)[i][k] * B[k][j];
                    _row[j] = _sum;
                }
                this->set_row(i, _row);
            }
            return *this;
        }

    };

    template <class T>
    std::ostream& operator<< (std::ostream& out, const matrix<T>& A) { return out << A.pretty(); }

    template <class T>
    matrix<T> operator+ (const matrix<T>& A, const matrix<T>& B) {
        matrix<T> _Tmp(A);
        _Tmp += B;
        return _Tmp;
    }

    template <class T>
    matrix<T> operator- (const matrix<T>& A, const matrix<T>& B) {
        matrix<T> _Tmp(A);
        _Tmp -= B;
        return _Tmp;
    }

    template <class T>
    matrix<T> operator* (const matrix<T>& A, const matrix<T>& B) {
        matrix<T> _Tmp(A);
        _Tmp *= B;
        return _Tmp;
    }

    template <class T>
    matrix<T> operator* (const matrix<T>& A, T _koef) {
        matrix<T> _Tmp(A);
        _Tmp *= _koef;
        return _Tmp;
    }

    template <class T>
    matrix<T> operator* (T _koef, const matrix<T>& A) {
        return A * _koef;
    }

    template <class T>
    matrix<T> operator/ (const matrix<T>& A, T _koef) {
        matrix<T> _Tmp(A);
        _Tmp /= _koef;
        return _Tmp;
    }

    template <typename T>
    matrix<T> identity_matrix (std::size_t _Count) {
        matrix<T> A(_Count, std::vector<T>(_Count));
        for (size_t i = 0; i < A.size_rows(); i++)
            A[i][i] = 1;
        return A;
    }
}
#endif /// _SIMPLE_MATRIX_HPP
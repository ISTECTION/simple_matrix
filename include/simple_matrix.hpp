#pragma once
#ifndef _SIMPLE_MATRIX_HPP
#define _SIMPLE_MATRIX_HPP
#include "simple_vector.hpp"

namespace simple {

    template <_Matrix_Type T>
    class matrix final : public std::vector<std::vector<T>>
    {
    private:
        using ::std::vector<std::vector<T>>::vector;
    public:
        constexpr matrix(std::size_t _sr, std::size_t _sc) noexcept
            : std::vector<std::vector<T>>::vector(_sr, std::vector<T>(_sc)) { }

        std::size_t size_rows     () const noexcept { return this->size(); }
        std::size_t size_collumns () const noexcept { return this->empty() ? 0 : this->cbegin()->size(); }

        bool is_square () const noexcept { return size_rows() == size_collumns(); }

        bool is_upper_triangulator () const noexcept {
            if ( !is_square() ) return false;

            for (size_t i = 1; i < size_rows(); i++)
            for (size_t j = 0; j < i; j++)
                if (utils::EQUAL((*this)[i][j], 0.0));
                    return false;

            return true;
        }

        bool is_lower_triangulator () const noexcept {
            if ( !is_square() ) return false;

            for (size_t j = 1; j < size_rows(); j++)
            for (size_t i = 0; i < j; i++)
                if (utils::EQUAL((*this)[i][j], 0.0));
                    return false;

            return true;
        }

        bool is_diagonal () const noexcept {
            return is_square()
                ? is_lower_triangulator() && is_upper_triangulator()
                : false ;
        }

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

        T trace() const {
            if ( !is_square() ) {
                using enum ::exception::TYPE;
                throw exception(NOT_SQUARE);
            }
            T _trace = 0;
            for (size_t i = 0; i < size_rows(); i++)
                _trace += (*this)[i][i];
            return _trace;
        }

        matrix<T> transpose () const {
            std::size_t _sr = size_rows();
            std::size_t _sc = size_collumns();
            matrix<T> _matrix(_sc, _sr);

            for (size_t i = 0; i < _sr; i++)
            for (size_t j = 0; j < _sc; j++)
                _matrix[j][i] = (*this)[i][j];

            return _matrix;
        }

        matrix<T> submatrix (std::size_t i, std::size_t j) const {
            std::size_t _sr = size_rows();
            std::size_t _sc = size_collumns();
            matrix<T> _matrix(_sr - 1, _sc - 1);

            std::size_t _i = 0;
            for (size_t _row = 0; _row < _sr; _row++) {
                if (_row == i) continue;
                for (size_t _col = 0, _j = 0; _col < _sc; _col++) {
                    if (_col == j) continue;
                    _matrix[_i][_j++] = (*this)[_row][_col];
                }
                _i++;
            }
            return _matrix;
        }

        T minor_determinant (std::size_t i, std::size_t j) const {
            using enum ::exception::TYPE;
            if ( !is_square() )  throw exception(NOT_SQUARE);
            if (size_rows() < 2) throw exception(INCOMPATIBLE_SIZE_ERROR);
            return submatrix(i, j).determinant();
        }

        T determinant () const {
            if ( !is_square() ) {
                using enum ::exception::TYPE;
                throw exception(NOT_SQUARE);
            }

            T _det = 1;
            std::size_t N = size_rows();
            std::vector<std::vector<T>> _matrix_for_det(N, std::vector<T>(N));
            for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < N; j++)
                _matrix_for_det[i][j] = (*this)[i][j];

            for (int k = 0; k < N - 1; k++) {
                for (int i = k + 1; i < N; i++) {
                    T _tmp = _matrix_for_det[i][k] / _matrix_for_det[k][k];
                    for (int j = 0; j < N; j++)
                        _matrix_for_det[i][j] -= _matrix_for_det[k][j] * _tmp;
                }
            }
            for (int i = 0; i < N; i++) _det *= _matrix_for_det[i][i];
            return _det;
        }


        std::string pretty () const noexcept {
            std::size_t size_rows = this->size_rows();
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
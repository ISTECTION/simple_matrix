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
        using _STL_vector = ::std::vector<std::vector<T>>;
    public:
        constexpr matrix(std::size_t _sr, std::size_t _sc) noexcept
            : _STL_vector::vector(_sr, std::vector<T>(_sc)) { }

        std::size_t size_rows () const noexcept;

        std::size_t size_collumns () const noexcept;


        bool is_square () const noexcept;

        bool is_upper_triangulator () const noexcept;

        bool is_lower_triangulator () const noexcept;

        bool is_diagonal () const noexcept;


        simple::vector<T> get_row (std::size_t _row) const;

        simple::vector<T> get_collumn (std::size_t _col) const;

        void set_row (std::size_t _row, const simple::vector<T>& _row_v);

        void set_collumn (std::size_t _col, const simple::vector<T>& _col_v);


        matrix<T> transpose () const;

        matrix<T> submatrix (std::size_t i, std::size_t j) const;

        matrix<T> minor_matrix () const;

        matrix<T> cofactor_matrix () const;

        matrix<T> adj () const;

        matrix<T> invert () const;


        T trace() const;

        T minor_determinant (std::size_t i, std::size_t j) const;

        T cofactor (std::size_t i, std::size_t j) const;

        T determinant () const;


        std::string pretty () const noexcept;


        matrix<T>& operator+= (const matrix<T>& A);

        matrix<T>& operator-= (const matrix<T>& A);

        matrix<T>& operator*= (const matrix<T>& B);

        matrix<T>& operator*= (double _koef);

        matrix<T>& operator/= (double _koef);
    };

    template <_Matrix_Type T>
    std::size_t matrix<T>::size_rows () const noexcept {
        return this->size();
    }

    template <_Matrix_Type T>
    std::size_t matrix<T>::size_collumns () const noexcept {
        return this->empty() ? 0 : this->cbegin()->size();
    }

    template <_Matrix_Type T>
    bool matrix<T>::is_square () const noexcept {
        return size_rows() == size_collumns();
    }

    template <_Matrix_Type T>
    bool matrix<T>::is_upper_triangulator () const noexcept {
        if ( !is_square() ) return false;

        for (size_t i = 1; i < size_rows(); i++)
        for (size_t j = 0; j < i; j++)
            if (not utils::EQUAL((*this)[i][j], 0))
                return false;
        return true;
    }

    template <_Matrix_Type T>
    bool matrix<T>::is_lower_triangulator () const noexcept {
        if ( !is_square() ) return false;

        for (size_t j = 1; j < size_rows(); j++)
        for (size_t i = 0; i < j; i++)
            if (not utils::EQUAL((*this)[i][j], 0))
                return false;
        return true;
    }

    template <_Matrix_Type T>
    bool matrix<T>::is_diagonal () const noexcept {
        return is_square()
            ? is_lower_triangulator() && is_upper_triangulator()
            : false ;
    }

    template <_Matrix_Type T>
    simple::vector<T> matrix<T>::get_row (std::size_t _row) const {
        return simple::vector<T>(this->at(_row));
    }

    template <_Matrix_Type T>
    simple::vector<T> matrix<T>::get_collumn (std::size_t _col) const {
        if (_col >= size_collumns()) {
            using enum ::exception::TYPE;
            throw exception(INDEX_COLLUMN_ERROR);
        }
        simple::vector<T> _col_v(this->size());
        for (size_t i = 0; i < this->size(); i++)
            _col_v[i] = (*this)[i][_col];
        return _col_v;
    }

    template <_Matrix_Type T>
    void matrix<T>::set_row (std::size_t _row, const simple::vector<T>& _row_v) {
        if (_row >= size_rows()) {
            using enum ::exception::TYPE;
            throw exception(INDEX_ROW_ERROR);
        }
        (*this)[_row] = _row_v;
    }

    template <_Matrix_Type T>
    void matrix<T>::set_collumn (std::size_t _col, const simple::vector<T>& _col_v) {
        if (_col >= size_collumns()) {
            using enum ::exception::TYPE;
            throw exception(INDEX_COLLUMN_ERROR);
        }
        for (size_t i = 0; i < this->size(); i++)
            (*this)[i][_col] = _col_v[i];
    }

    template <_Matrix_Type T>
    matrix<T> matrix<T>::transpose () const {
        std::size_t _sr = size_rows();
        std::size_t _sc = size_collumns();
        matrix<T> _matrix(_sc, _sr);

        for (size_t i = 0; i < _sr; i++)
        for (size_t j = 0; j < _sc; j++)
            _matrix[j][i] = (*this)[i][j];
        return _matrix;
    }

    template <_Matrix_Type T>
    matrix<T> matrix<T>::submatrix (std::size_t i, std::size_t j) const {
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

    template <_Matrix_Type T>
    matrix<T> matrix<T>::minor_matrix () const {
        if ( !is_square() ) {
            using enum ::exception::TYPE;
            throw exception(NOT_SQUARE);
        }
        std::size_t _sr = size_rows();
        std::size_t _sc = size_collumns();
        matrix<T> A(_sr, _sc);
        for (size_t i = 0; i < _sr; ++i)
        for (size_t j = 0; j < _sc; ++j)
            A[i][j] = minor_determinant(i, j);
        return A;
    }

    template <_Matrix_Type T>
    matrix<T> matrix<T>::cofactor_matrix () const {
        matrix<T> A = minor_matrix();

        for (size_t i = 0; i < size_rows(); i++)
        for (size_t j = i + 1; j < size_collumns(); j++)
            if ((i + j) % 2) {
                A[i][j] = -A[i][j];
                A[j][i] = -A[j][i];
            }
        return A;
    }

    template <_Matrix_Type T>
    matrix<T> matrix<T>::adj () const {
        return cofactor_matrix().transpose();
    }

    template <_Matrix_Type T>
    matrix<T> matrix<T>::invert () const {
        using enum ::exception::TYPE;
        if ( !is_square() )
            throw exception(NOT_SQUARE);

        T _det = determinant();
        if (_det == 0)
            throw exception(NOT_INVERTIBLE);

        return size_rows() == 2
            ? matrix<T> {
                {  (*this)[1][1], -(*this)[0][1]  },
                { -(*this)[1][0],  (*this)[0][0]  }
            }
            : adj() / _det;
    }

    template <_Matrix_Type T>
    T matrix<T>::trace () const {
        if ( !is_square() ) {
            using enum ::exception::TYPE;
            throw exception(NOT_SQUARE);
        }
        T _trace = 0;
        for (size_t i = 0; i < size_rows(); i++)
            _trace += (*this)[i][i];
        return _trace;
    }

    template <_Matrix_Type T>
    T matrix<T>::minor_determinant (std::size_t i, std::size_t j) const {
        using enum ::exception::TYPE;
        if ( !is_square() )  throw exception(NOT_SQUARE);
        if (size_rows() < 2) throw exception(INCOMPATIBLE_SIZE_ERROR);
        return submatrix(i, j).determinant();
    }

    template <_Matrix_Type T>
    T matrix<T>::cofactor (std::size_t i, std::size_t j) const {
        T _det = minor_determinant(i, j);
        return ((i + j) % 2 ? -1 : 1) * _det;
    }

    template <_Matrix_Type T>
    T matrix<T>::determinant () const {
        if ( !is_square() ) {
            using enum ::exception::TYPE;
            throw exception(NOT_SQUARE);
        }

        T _det = 1;
        std::size_t N = size_rows();
        _STL_vector _matrix_for_det(N, std::vector<T>(N));
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

    template <_Matrix_Type T>
    std::string matrix<T>::pretty () const noexcept {
        std::size_t size_rows = this->size_rows();
        std::size_t size_collumns = this->size_collumns();

        if (size_rows == 0 || size_collumns == 0) { return std::string { "empty" }; }

        if constexpr (std::is_integral<T>::value or std::is_floating_point<T>::value) {

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

            std::size_t midwidth = (mwidth * size_collumns) + ((size_collumns + 1) << 1);
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

        } else {
            return
            std::string { "I can't process this type" };
        }
    }

    template <_Matrix_Type T>
    matrix<T>& matrix<T>::operator+= (const matrix<T>& A) {
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

    template <_Matrix_Type T>
    matrix<T>& matrix<T>::operator-= (const matrix<T>& A) {
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

    template <_Matrix_Type T>
    matrix<T>& matrix<T>::operator*= (const matrix<T>& B) {
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

    template <_Matrix_Type T>
    matrix<T>& matrix<T>::operator*= (double _koef) {
        std::size_t _sizecollumn = size_collumns();
        for (size_t i = 0; i < this->size(); i++)
        for (size_t j = 0; j < _sizecollumn; j++)
            (*this)[i][j] *= _koef;
        return *this;
    }

    template <_Matrix_Type T>
    matrix<T>& matrix<T>::operator/= (double _koef) {
        std::size_t _sizecollumn = size_collumns();
        for (size_t i = 0; i < this->size(); i++)
        for (size_t j = 0; j < _sizecollumn; j++)
            (*this)[i][j] /= _koef;
        return *this;
    }

    template <_Matrix_Type T>
    std::ostream& operator<< (std::ostream& out, const matrix<T>& A) { return out << A.pretty(); }

    template <_Matrix_Type T>
    matrix<T> operator+ (const matrix<T>& A, const matrix<T>& B) {
        matrix<T> _Tmp(A);
        _Tmp += B;
        return _Tmp;
    }

    template <_Matrix_Type T>
    matrix<T> operator- (const matrix<T>& A, const matrix<T>& B) {
        matrix<T> _Tmp(A);
        _Tmp -= B;
        return _Tmp;
    }

    template <_Matrix_Type T>
    matrix<T> operator* (const matrix<T>& A, const matrix<T>& B) {
        matrix<T> _Tmp(A);
        _Tmp *= B;
        return _Tmp;
    }

    template <_Matrix_Type T>
    matrix<T> operator* (const matrix<T>& A, T _koef) {
        matrix<T> _Tmp(A);
        _Tmp *= _koef;
        return _Tmp;
    }

    template <_Matrix_Type T>
    matrix<T> operator* (T _koef, const matrix<T>& A) {
        return A * _koef;
    }

    template <_Matrix_Type T>
    matrix<T> operator/ (const matrix<T>& A, T _koef) {
        matrix<T> _Tmp(A);
        _Tmp /= _koef;
        return _Tmp;
    }

    template <_Matrix_Type T>
    matrix<T> identity_matrix (std::size_t _Count) {
        matrix<T> A(_Count, std::vector<T>(_Count));
        for (size_t i = 0; i < A.size_rows(); i++)
            A[i][i] = 1;
        return A;
    }

    template <_File_type T, _Matrix_Type U>
    void read (matrix<U>& _matrix, T _path) {

        std::ifstream i_file(_path);
        if (i_file.is_open()) {
            _matrix.clear();
            std::string _line;
            while (std::getline(i_file, _line)) {
                std::istringstream _istream(_line);
                std::vector<U> _row;
                std::copy(
                    std::istream_iterator<U>(_istream),
                    std::istream_iterator<U>(),
                    std::back_inserter(_row));
                if (_row.size() > 0) {
                    _matrix.push_back(_row);
                }
            }
            i_file.close();
        } else {
            using enum ::exception::TYPE;
            throw exception(FILE_OPENING_ERROR);
        }
    }

    template <_File_type T, _Matrix_Type U>
    void read (matrix<U>& _matrix, T _path, std::size_t _row_count, std::size_t _col_count) {

        std::ifstream i_file(_path);
        if (i_file.is_open()) {
            _matrix.clear();
            _matrix.resize(_row_count, std::vector<U>(_col_count));

            for (size_t i = 0; i < _row_count; i++)
            for (size_t j = 0; j < _col_count; j++)
                i_file >> _matrix[i][j];

            i_file.close();
        } else {
            using enum ::exception::TYPE;
            throw exception(FILE_OPENING_ERROR);
        }
    }

    template <_File_type T, _Matrix_Type U>
    void write (const matrix<U>& _matrix, T _path) {

        std::ofstream o_file(_path);
        if (o_file.is_open()) {
            for (const auto& _row : _matrix) {
                for (const auto& _elem : _row)
                    o_file << _elem << ' ';
                o_file << '\n';
            }
            o_file.close();
        } else {
            using enum ::exception::TYPE;
            throw exception(FILE_OPENING_ERROR);
        }
    }
}
#endif /// _SIMPLE_MATRIX_HPP
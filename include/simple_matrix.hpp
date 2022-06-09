#pragma once
#ifndef _SIMPLE_MATRIX_HPP
#define _SIMPLE_MATRIX_HPP
#include "simple_vector.hpp"

namespace simple {

    /** @class simple::matrix
      * @brief Простой матричный класс
      * @details В данном классе реализованы все
      * возможные функции взаимодействия с матрицами
      * @tparam T Любые целочисленные и вещественные типы
      */
    template <_Matrix_Type T>
    class matrix final : public std::vector<std::vector<T>>
    {
    private:
        using ::std::vector<std::vector<T>>::vector;
        using _STL_vector = ::std::vector<std::vector<T>>;
    public:
        constexpr matrix(std::size_t _sr, std::size_t _sc) noexcept
            : _STL_vector::vector(_sr, std::vector<T>(_sc)) { }

        /** @fn std::size_t size_rows () const noexcept
          * @return Количество строк матрицы
          */
        std::size_t size_rows () const noexcept;

        /** @fn std::size_t size_collumns () const noexcept
          * @return Количество столбцов матрицы
          */
        std::size_t size_collumns () const noexcept;

        /** @fn bool is_square () const noexcept
          * @return
          *     - true  : Если матрица является квадратной
          *     - false : Если матрица не является квадратной
          */
        bool is_square () const noexcept;

        /** @fn bool is_rectangular_matrix () const noexcept
          * @return
          *     - true  : Если матрица является прямоугольной
          *     - false : Если матрица не является прямоугольной
          */
        bool is_rectangular_matrix () const noexcept;

        /** @fn bool is_upper_triangulator () const noexcept
          * @return
          *     - true  : Если матрица является верхнетреугольной
          *     - false : Если матрица не является верхнетреугольной
          */
        bool is_upper_triangulator () const noexcept;

        /** @fn bool is_lower_triangulator () const noexcept
          * @return
          *     - true  : Если матрица является нижнетреугольной
          *     - false : Если матрица не является нижнетреугольной
          */
        bool is_lower_triangulator () const noexcept;

        /** @fn bool is_diagonal () const noexcept
          * @return
          *     - true  : Если матрица является диагональной
          *     - false : Если матрица не является диагональной
          */
        bool is_diagonal () const noexcept;

        /** @fn bool is_identity_matrix () const noexcept
          * @return
          *     - true  : Если матрица является единичной
          *     - false : Если матрица не является единичной
          */
        bool is_identity_matrix () const noexcept;


        /** @fn simple::vector<T> get_row (std::size_t) const
          * @brief Получить строку матрицы
          * @param _row Номер строки
          * @return Вектор
          */
        simple::vector<T> get_row (std::size_t _row) const;

        /** @fn simple::vector<T> get_collumn (std::size_t) const
          * @brief Получить столбец матрицы
          * @param _col Номер столбца
          * @return Вектор
          */
        simple::vector<T> get_collumn (std::size_t _col) const;

        /** @fn void set_row (std::size_t, const simple::vector<T>&)
          * @brief Установить строку в матрицу
          * @param _row   Номер строки
          * @param _row_v Вектор
          */
        void set_row (std::size_t _row, const simple::vector<T>& _row_v);

        /** @fn void set_collumn (std::size_t, const simple::vector<T>&)
          * @brief Установить столбец в матрицу
          * @param _col   Номер столбца
          * @param _col_v Вектор
          */
        void set_collumn (std::size_t _col, const simple::vector<T>& _col_v);

        /** @fn matrix<T> transpose () const
          * @brief Получить транспонированную матрицу
          * @return Транспонированную матрицу
          */
        matrix<T> transpose () const;

        /** @fn matrix<T> submatrix (std::size_t, std::size_t) const
          * @brief Получить подматрицу
          * @param i Номер строки
          * @param j Номер столбца
          * @return Подматрицу
          */
        matrix<T> submatrix (std::size_t i, std::size_t j) const;

        matrix<T> minor_matrix () const;

        matrix<T> cofactor_matrix () const;

        matrix<T> adj () const;

        matrix<T> invert () const;


        [[nodiscard]] constexpr T trace() const;

        [[nodiscard]] constexpr T minor_determinant (std::size_t i, std::size_t j) const;

        [[nodiscard]] constexpr T cofactor (std::size_t i, std::size_t j) const;

        [[nodiscard]] constexpr T determinant () const;


        /** @fn std::string pretty () const noexcept
          * @return Строку содержащую распечтанный вектор

          * @addtogroup pretty
          * @{
          */
        std::string pretty () const noexcept;
        /** @} */

        /** @fn matrix<T>& operator+= (const matrix<T>&)
          * @brief Перегрузка операции сложения
          * @param A Матрица с которой будет произведено сложение
          * @return Ссылка на текущий экземпляр класса
          */
        matrix<T>& operator+= (const matrix<T>& A);

        /** @fn matrix<T>& operator-= (const matrix<T>&)
          * @brief Перегрузка операции вычитания
          * @param A Матрица которая будет вычтена
          * @return Ссылка на текущий экземпляр класса
          */
        matrix<T>& operator-= (const matrix<T>& A);

        /** @fn matrix<T>& operator*= (const matrix<T>&)
          * @brief Перегрузка операции умножения
          * @param B Матрица на которую будет произведено умножение
          * @return Ссылка на текущий экземпляр класса
          */
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
    bool matrix<T>::is_rectangular_matrix () const noexcept {
        return size_rows() != size_collumns();
    }

    template <_Matrix_Type T>
    bool matrix<T>::is_upper_triangulator () const noexcept {
        if (is_rectangular_matrix()) return false;

        using std::views::iota;
        for (size_t i : iota(0ull, this->size()))
        for (size_t j : iota(0ull, i))
            if (not utils::EQUAL((*this)[i][j], 0))
                return false;
        return true;
    }

    template <_Matrix_Type T>
    bool matrix<T>::is_lower_triangulator () const noexcept {
        if (is_rectangular_matrix()) return false;

        using std::views::iota;
        for (size_t j : iota(0ull, this->size()))
        for (size_t i : iota(0ull, j))
            if (not utils::EQUAL((*this)[i][j], 0))
                return false;
        return true;
    }

    template <_Matrix_Type T>
    bool matrix<T>::is_diagonal () const noexcept {
        return is_rectangular_matrix()
            ? false
            : is_lower_triangulator() &&
              is_upper_triangulator() ;
    }

    template <_Matrix_Type T>
    bool matrix<T>::is_identity_matrix () const noexcept {
        if (is_rectangular_matrix()) return false;
        for (size_t i : std::views::iota(0ull, this->size()))
            if (not utils::EQUAL((*this)[i][i], 1))
                return false;
        return true;
    }

    template <_Matrix_Type T>
    simple::vector<T> matrix<T>::get_row (std::size_t _row) const {
        return simple::vector<T>(this->at(_row));
    }

    template <_Matrix_Type T>
    simple::vector<T> matrix<T>::get_collumn (std::size_t _col) const {
        if (_col >= size_collumns()) {
            using enum exception::TYPE;
            throw exception(INDEX_COLLUMN_ERROR);
        }
        simple::vector<T> _col_v(this->size());
        for (size_t i : std::views::iota(0ull, this->size()))
            _col_v[i] = (*this)[i][_col];
        return _col_v;
    }

    template <_Matrix_Type T>
    void matrix<T>::set_row (std::size_t _row, const simple::vector<T>& _row_v) {
        if (_row >= size_rows()) {
            using enum exception::TYPE;
            throw exception(INDEX_ROW_ERROR);
        }
        (*this)[_row] = _row_v;
    }

    template <_Matrix_Type T>
    void matrix<T>::set_collumn (std::size_t _col, const simple::vector<T>& _col_v) {
        if (_col >= size_collumns()) {
            using enum exception::TYPE;
            throw exception(INDEX_COLLUMN_ERROR);
        }
        for (size_t i : std::views::iota(0ull, this->size()))
            (*this)[i][_col] = _col_v[i];
    }

    template <_Matrix_Type T>
    matrix<T> matrix<T>::transpose () const {
        std::size_t _sr = size_rows();
        std::size_t _sc = size_collumns();
        matrix<T> _matrix(_sc, _sr);

        using std::views::iota;
        for (size_t i : iota(0ull, _sr))
        for (size_t j : iota(0ull, _sc))
            _matrix[j][i] = (*this)[i][j];
        return _matrix;
    }

    template <_Matrix_Type T>
    matrix<T> matrix<T>::submatrix (std::size_t i, std::size_t j) const {
        std::size_t _sr = size_rows();
        std::size_t _sc = size_collumns();
        matrix<T> _matrix(_sr - 1, _sc - 1);

        std::size_t _i = 0;
        using std::views::iota;
        for (size_t _row : iota(0ull, _sr)) {
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
        if (is_rectangular_matrix()) {
            using enum exception::TYPE;
            throw exception(NOT_SQUARE);
        }
        std::size_t _sr = size_rows();
        std::size_t _sc = size_collumns();
        matrix<T> A(_sr, _sc);
        using std::views::iota;
        for (size_t i : iota(0ull, _sr))
        for (size_t j : iota(0ull, _sc))
            A[i][j] = minor_determinant(i, j);
        return A;
    }

    template <_Matrix_Type T>
    matrix<T> matrix<T>::cofactor_matrix () const {
        matrix<T> A = minor_matrix();

        for (size_t i : iota(0ull,  this->size()))
        for (size_t j : iota(i + 1, size_collumns()))
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
        using enum exception::TYPE;
        if (is_rectangular_matrix())
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
    constexpr T matrix<T>::trace () const {
        if (is_rectangular_matrix()) {
            using enum exception::TYPE;
            throw exception(NOT_SQUARE);
        }
        T _trace = 0;
        for (size_t i : std::views::iota(0ull, this->size()))
            _trace += (*this)[i][i];
        return _trace;
    }

    template <_Matrix_Type T>
    constexpr T matrix<T>::minor_determinant (std::size_t i, std::size_t j) const {
        using enum ::exception::TYPE;
        if (is_rectangular_matrix()) throw exception(NOT_SQUARE);
        if (size_rows() < 2) throw exception(INCOMPATIBLE_SIZE_ERROR);
        return submatrix(i, j).determinant();
    }

    template <_Matrix_Type T>
    constexpr T matrix<T>::cofactor (std::size_t i, std::size_t j) const {
        T _det = minor_determinant(i, j);
        return ((i + j) % 2 ? -1 : 1) * _det;
    }

    template <_Matrix_Type T>
    constexpr T matrix<T>::determinant () const {
        if (is_rectangular_matrix()) {
            using enum exception::TYPE;
            throw exception(NOT_SQUARE);
        }
        std::size_t N = size_rows();

        using _STL_vector_d = std::vector<std::vector<double>>;
        _STL_vector_d _matrix_for_det(N, std::vector<double>(N));

        using std::views::iota;
        for (size_t i : iota(0ull, N))
        for (size_t j : iota(0ull, N))
            _matrix_for_det[i][j] = (*this)[i][j];

        for (size_t k : iota(0ull, N - 1)) {
            for (size_t i : iota(k + 1, N)) {
                double _tmp = _matrix_for_det[i][k] / _matrix_for_det[k][k];
                for (size_t j : iota(0ull, N))
                    _matrix_for_det[i][j] -= _matrix_for_det[k][j] * _tmp;
            }
        }

        double _det { 1 };
        for (size_t i : iota(0ull, N))
            _det *= _matrix_for_det[i][i];
        return _det;
    }

    template <_Matrix_Type T>
    std::string matrix<T>::pretty () const noexcept {
        std::size_t _sr = this->size_rows();
        std::size_t _sc = this->size_collumns();

        if (_sr == 0 || _sc == 0) { return std::string { "empty" }; }

        if constexpr (std::is_integral<T>::value or std::is_floating_point<T>::value) {

            std::ostringstream osstr, main;
            std::vector<std::string> strs;
            std::size_t mwidth = 0;
            using std::views::iota;
            for (size_t i : iota(0ull, _sr)) {
                for (size_t j : iota(0ull, _sc)) {
                    double term = (*this)[i][j];
                    osstr << (utils::EQUAL( term, 0.0 ) ? 0 : term);
                    std::string str = osstr.str();
                    osstr.str(std::string { });
                    strs.push_back(str);
                    std::size_t nl = str.size();
                    mwidth = nl > mwidth ? nl : mwidth;
                }
            }

            std::size_t midwidth = (mwidth * _sc) + ((_sc + 1) << 1);
            main << "┌─" << std::setw(midwidth - 2) << "" << "─┐";
            for (size_t i : iota(0ull, _sr)) {
                main << '\n' << "│";
                for (size_t j : iota(0ull, _sc)) {
                    std::string str = strs[i * _sc + j];
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
            using enum exception::TYPE;
            throw exception(INCOMPATIBLE_SIZE_ERROR);
        }
        for (size_t i : std::views::iota(0ull, _sr))
        for (size_t j : std::views::iota(0ull, _sc))
            (*this)[i][j] += A[i][j];
        return *this;
    }

    template <_Matrix_Type T>
    matrix<T>& matrix<T>::operator-= (const matrix<T>& A) {
        std::size_t _sr = size_rows();
        std::size_t _sc = size_collumns();

        if (_sr != A.size_rows() || _sc != A.size_collumns()) {
            using enum exception::TYPE;
            throw exception(INCOMPATIBLE_SIZE_ERROR);
        }
        for (size_t i : std::views::iota(0ull, _sr))
        for (size_t j : std::views::iota(0ull, _sc))
            (*this)[i][j] -= A[i][j];
        return *this;
    }

    template <_Matrix_Type T>
    matrix<T>& matrix<T>::operator*= (const matrix<T>& B) {
        if (size_collumns() != B.size_rows()) {
            using enum exception::TYPE;
            throw exception(INCOMPATIBLE_SIZE_ERROR);
        }
        std::size_t _Asr = size_rows();
        std::size_t _Bsc = B.size_collumns();
        using std::views::iota;
        for (size_t i : iota(0ull, _Asr)) {
            simple::vector<T> _row(_Bsc);
            for (size_t j : iota(0ull, _Bsc)) {
                T _sum = 0;
                for (size_t k : iota(0ull, size_collumns()))
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
        using std::views::iota;
        for (size_t i : iota(0ull, this->size()))
        for (size_t j : iota(0ull, _sizecollumn))
            (*this)[i][j] *= _koef;
        return *this;
    }

    template <_Matrix_Type T>
    matrix<T>& matrix<T>::operator/= (double _koef) {
        std::size_t _sizecollumn = size_collumns();
        using std::views::iota;
        for (size_t i : iota(0ull, this->size()))
        for (size_t j : iota(0ull, _sizecollumn))
            (*this)[i][j] /= _koef;
        return *this;
    }

    /** @fn std::ostream& operator<< (std::ostream&, const matrix<T>&)
      * @brief  Вывод матрицы в поток
      * @tparam T Любые целочисленные и вещественные типы
      * @param _out Поток для записи матрицы
      * @param _mtx Сама матрица
      */
    template <_Matrix_Type T>
    std::ostream& operator<< (std::ostream& _out, const matrix<T>& _mtx) { return _out << _mtx.pretty(); }

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

    /** @fn matrix<T> identity_matrix (std::size_t)
      * @brief Возвращает единичную матрицу
      * @param _Count Размерность матрицы
      * @return Единичную матрицу
      */
    template <_Matrix_Type T>
    matrix<T> identity_matrix (std::size_t _Count) {
        matrix<T> A(_Count, std::vector<T>(_Count));
        for (size_t i = 0; i < A.size_rows(); i++)
            A[i][i] = 1;
        return A;
    }

    /** @fn void read (matrix<U>&, T)
      * @brief  Чтение матрицы из файла неизвестного размера
      * @tparam U Любые целочисленные и вещественные типы
      * @tparam T std::filesystem::path || std::string
      * @param[out] _matrix Матрица в которую будет произведена запись
      * @param[in]  _path  Путь до файла
      * @exception exception::TYPE::FILE_OPENING_ERROR В случае неудачи при открытии файла
      */
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
            using enum exception::TYPE;
            throw exception(FILE_OPENING_ERROR);
        }
    }

    /** @fn void read (matrix<U>&, T, std::size_t, std::size_t)
      * @brief  Чтение матрицы из файла известного размера
      * @tparam U Любые целочисленные и вещественные типы
      * @tparam T std::filesystem::path || std::string
      * @param[out] _matrix Матрица в которую будет произведена запись
      * @param[in]  _path  Путь до файла
      * @param[in]  _row_count Количество строк матрицы
      * @param[in]  _col_count Количество столбцов матрицы
      * @exception exception::TYPE::FILE_OPENING_ERROR В случае неудачи при открытии файла
      */
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

    /** @fn void write (const matrix<U>&, T)
      * @brief  Записать матрицу в файл
      * @tparam U Любые целочисленные и вещественные типы
      * @tparam T std::filesystem::path || std::string
      * @param _matrix Сохраняемая матрица
      * @param _path Путь к файлу
      * @exception exception::TYPE::FILE_OPENING_ERROR В случае неудачи при открытии файла
      */
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
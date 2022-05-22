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
        std::size_t size_row     () const noexcept { return this->size(); }
        std::size_t size_collumn () const noexcept { return this->empty() ? 0 : this->cbegin()->size(); }

        simple::vector<T> get_row (std::size_t _row) const {
            return simple::vector<T>(this->at(_row));
        }

        simple::vector<T> get_collumn (std::size_t _col) const {
            if (_col >= size_collumn()) {
                using enum ::exception::TYPE;
                throw exception(INDEX_COLLUMN_ERROR);
            }
            simple::vector<T> _col_v(this->size());
            for (size_t i = 0; i < this->size(); i++)
                _col_v[i] = (*this)[i][_col];
            return _col_v;
        }

        void set_row (std::size_t _row, const simple::vector<T>& _row_v) {
            if (_row >= size_row()) {
                using enum ::exception::TYPE;
                throw exception(INDEX_ROW_ERROR);
            }
            (*this)[_row] = _row_v;
        }

        void set_collumn (std::size_t _col, const simple::vector<T>& _col_v) {
            if (_col >= size_collumn()) {
                using enum ::exception::TYPE;
                throw exception(INDEX_COLLUMN_ERROR);
            }
            for (size_t i = 0; i < this->size(); i++)
                (*this)[i][_col] = _col_v[i];
        }

        std::string pretty () const noexcept {
            if (size_row() == 0 || size_collumn() == 0) { return std::string { "empty" }; }

            std::ostringstream osstr, main;
            std::vector<std::string> strs;
            std::size_t mwidth = 0;
            std::size_t size_row     = this->size_row();
            std::size_t size_collumn = this->size_collumn();

            for (size_t i = 0; i < size_row; ++i) {
                for (size_t j = 0; j < size_collumn; ++j) {
                    double term = (*this)[i][j];
                    osstr << (utils::EQUAL( term, 0.0 ) ? 0 : term);
                    std::string str = osstr.str();
                    osstr.str(std::string { });
                    strs.push_back(str);
                    std::size_t nl = str.size();
                    mwidth = nl > mwidth ? nl : mwidth;
                }
            }

            std::size_t midwidth = (mwidth * size_row) + ((size_row + 1) << 1);
            main << "┌─" << std::setw(midwidth - 2) << "" << "─┐";
            for (size_t i = 0; i < size_row; i++) {
                main << '\n' << "│";
                for (size_t j = 0; j < size_collumn; j++) {
                    std::string str = strs[i * size_collumn + j];
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




    };
}

#endif /// _SIMPLE_MATRIX_HPP
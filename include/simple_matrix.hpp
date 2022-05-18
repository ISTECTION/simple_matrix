#ifndef _SIMPLE_MATRIX_HPP
#define _SIMPLE_MATRIX_HPP
#include "simple_vector.hpp"

namespace simple {

    template <class T>
    class matrix : public std::vector<std::vector<T>>
    {
    private:
        using ::std::vector<std::vector<T>>::vector;
    public:
        simple::vector<T> get_row (std::size_t _row) const {
            return simple::vector<T>(this->at(_row));
        }

        simple::vector<T> get_collumn (std::size_t _col) const {
            simple::vector<T> _col_v(this->size());
            for (std::size_t i = 0; i < this->size(); i++)
                _col_v[i] = (*this)[i][_col];
            return _col_v;
        }
    };

}

#endif /// _SIMPLE_MATRIX_HPP
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
    };

}

#endif /// _SIMPLE_MATRIX_HPP
#ifndef _SIMPLE_MATRIX_HPP
#define _SIMPLE_MATRIX_HPP
#include <vector>

namespace simple {

    template <class T>
    class matrix : std::vector<std::vector<T>>
    {
    private:
        using ::std::vector<std::vector<T>>::vector;
    public:

    };

}

#endif /// _SIMPLE_MATRIX_HPP
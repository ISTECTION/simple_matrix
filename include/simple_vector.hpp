#ifndef _SIMPLE_VECTOR_HPP
#define _SIMPLE_VECTOR_HPP
#include <numeric>          /// std::accumulate
#include <vector>           /// std::vector


namespace simple {

    template <class T>
    class vector : public std::vector<T>
    {
    private:
        using ::std::vector<T>::vector;
    public:
        constexpr auto norm () const noexcept {
            return sqrt(
                std::inner_product(
                    this->begin(), this->end(), this->begin(), 0)
            );
        }

    };
}

#endif /// _SIMPLE_VECTOR_HPP
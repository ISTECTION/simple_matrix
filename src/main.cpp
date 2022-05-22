#include "simple_vector.hpp"
#include "simple_matrix.hpp"

#include <iostream>
#include <complex>

int main(int argc, const char *argv[]) {

    using namespace ::std::complex_literals;

    using ::std::complex;
    using ::std::double_t;

    simple::vector<double_t> a(3, 2);
    std::cout << "norm vector (a) : " << a.norm() << '\n';
    std::cout << a.pretty() << '\n';

    simple::matrix<double> m(3, std::vector<double>(3));
    m.set_row(1, { 1, 2, 3 });
    std::cout << m.pretty() << '\n';
    m.set_collumn(0, { 8, 7, 6 });
    std::cout << m.pretty() << '\n';

    return 0;
}
#include "simple_vector.hpp"
#include "simple_matrix.hpp"

#include <iostream>
#include <complex>

int main(int argc, const char *argv[]) {

    using namespace ::std::complex_literals;

    using ::std::complex;
    using ::std::double_t;

    // simple::vector<complex<double_t>> f(3, 2i * 1i + 8.8i);
    // f.at(0) = std::complex<double_t> { 2, 3 };

    // std::cout << "norm vector: " << f.norm() << std::endl;

    // for (const auto& _elem : f)
    //     std::cout
    //         << _elem.real() << " "
    //         << _elem.imag() << '\n';

    simple::vector<double_t> a(3, 2);
    std::cout << "norm vector (a) : " << a.norm() << '\n';





    return 0;
}

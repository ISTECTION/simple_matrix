#include "simple_vector.hpp"

#include <iostream>
#include <complex>

int main(int argc, const char *argv[]) {

    using namespace ::std::complex_literals;

    using ::std::complex;
    using ::std::double_t;

    simple_vector<complex<double_t>> f;

    f.resize(3, std::complex<double_t> { 2i * 1i });

    for (const auto& _elem : f)
        std::cout
            << _elem.real() << " "
            << _elem.imag() << '\n';


    return 0;
}

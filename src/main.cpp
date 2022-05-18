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


    simple::matrix<double> m(3, std::vector<double>(3));
    m.at(1).at(0) = 1;
    m.at(1).at(1) = 2;
    m.at(1).at(2) = 3;

    std::cout << "matrix row: "     << m.size()       << '\n';
    std::cout << "matrix collumn: " << m.at(0).size() << '\n';

    std::cout << "f : [ ";
    for (const auto& _el : m.get_row(1))
        std::cout << _el << ", ";
    std::cout << "]" << '\n';

    return 0;
}

#include "simple_vector.hpp"
#include "simple_matrix.hpp"

#include <iostream>
#include <complex>
#include <iomanip>

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

    simple::matrix<double> m2(3, std::vector<double>(3));
    m2.set_row(1, { 1, 2, 3 });
    m2.set_collumn(0, { 8, 7, 6 });

    m2 *= m;
    std::cout << m2 << '\n';
    std::cout << m2.transpose() << '\n';
    std::cout << m2.submatrix(1, 1) << '\n';


    simple::matrix<double> m_det(3, std::vector<double>(3));
    m_det.set_row(0, { 1, 2, 3});
    m_det.set_row(1, { 6, 5, 4});
    m_det.set_row(2, { 1, 4, 5});
    std::cout << "determinant: " << m_det.determinant() << '\n';
    std::cout << "minor_det: " << m_det.minor_determinant(1, 0) << '\n';
    std::cout << "cofactor: " << m_det.cofactor(1, 0) << '\n';

    return 0;
}
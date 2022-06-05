#include "../test_benchmark_data.hpp"
#include "simple_matrix.hpp"
#include "catch2/catch.hpp"

TEST_CASE("dimension of the matrix", "[size_rows] [size_collumns]") {
    simple::matrix<int> _mrx(3, 5);

    REQUIRE(_mrx.size_rows()     == 3);
    REQUIRE(_mrx.size_collumns() == 5);

    _mrx.clear();
    REQUIRE(_mrx.size_collumns() == 0);
}

TEST_CASE("square matrix check", "[is_square]") {
    simple::matrix<int> _mrx(3, 3);
    REQUIRE(_mrx.is_square());

    _mrx = simple::matrix<int>(3, std::vector<int>(5));
    REQUIRE_FALSE(_mrx.is_square());
}

TEST_CASE("upper triangulator matrix check", "[is_upper_triangulator] [is_lower_triangulator] [is_diagonal]") {
    simple::matrix<int> _mrx(3, 3);
    _mrx.set_row(0, { 1, 1, 1 });
    _mrx.set_row(1, { 1, 1, 1 });
    _mrx.set_row(2, { 1, 1, 1 });
    REQUIRE_FALSE(_mrx.is_upper_triangulator());
    REQUIRE_FALSE(_mrx.is_lower_triangulator());

    _mrx.set_row(1, { 0, 1, 1 });
    _mrx.set_row(2, { 0, 0, 1 });
    REQUIRE(_mrx.is_upper_triangulator());

    _mrx.set_row(0, { 1, 0, 0 });
    _mrx.set_row(1, { 0, 1, 0 });
    REQUIRE(_mrx.is_lower_triangulator());

    REQUIRE(_mrx.is_diagonal());

    _mrx = simple::matrix<int>(3, std::vector<int>(5));
    REQUIRE_FALSE(_mrx.is_upper_triangulator());
    REQUIRE_FALSE(_mrx.is_lower_triangulator());
    REQUIRE_FALSE(_mrx.is_diagonal());
}

TEST_CASE("take a row from the matrix", "[get_row]") {
    simple::matrix<int> _mrx(3, 3);
    _mrx.set_row(0, { 5, 6, 8 });
    _mrx.set_row(1, { 9, 3, 7 });
    _mrx.set_row(2, { 1, 4, 0 });

    using Catch::Matchers::Equals;
    REQUIRE_THAT(_mrx.get_row(0), Equals<int>({ 5, 6, 8 }));
    REQUIRE_THAT(_mrx.get_row(2), Equals<int>({ 1, 4, 0 }));

    REQUIRE_THROWS(_mrx.get_row(5));
}

TEST_CASE("take a collumn from the matrix", "[get_collumn]") {
    simple::matrix<int> _mrx(3, 3);
    _mrx.set_row(0, { 5, 6, 8 });
    _mrx.set_row(1, { 9, 3, 7 });
    _mrx.set_row(2, { 1, 4, 0 });

    using Catch::Matchers::Equals;
    REQUIRE_THAT(_mrx.get_collumn(0), Equals<int>({ 5, 9, 1 }));
    REQUIRE_THAT(_mrx.get_collumn(2), Equals<int>({ 8, 7, 0 }));

    REQUIRE_THROWS(_mrx.get_collumn(5));
}

TEST_CASE("inserting a row into a matrix", "[set_row]") {
    simple::matrix<int> _mrx(3, 3);
    REQUIRE_THROWS(_mrx.set_row(3, { 0, 0, 0 }));

    _mrx.set_row(0, { 1, 2, 3 });
    using Catch::Matchers::Equals;
    REQUIRE_THAT(_mrx.get_row(0), Equals<int>({ 1, 2, 3 }));
}

TEST_CASE("inserting a collumn into a matrix", "[set_collumn]") {
    simple::matrix<int> _mrx(3, 2);
    REQUIRE_THROWS(_mrx.set_collumn(2, { 0, 0, 0 }));

    _mrx.set_collumn(0, { 5, 4, 3 });
    using Catch::Matchers::Equals;
    REQUIRE_THAT(_mrx.get_collumn(0), Equals<int>({ 5, 4, 3 }));
}

TEST_CASE("transposed matrix", "[transpose]") {
    simple::matrix<int> _mrx = {
        { 1, 2 },
        { 3, 4 },
        { 5, 6 } };
    simple::matrix<int> _actual = _mrx.transpose();
    simple::matrix<int> _expected = {
        { 1, 3, 5 },
        { 2, 4, 6 } };
    REQUIRE(_expected == _actual);
}

TEST_CASE("submatrix matrix", "[submatrix]") {
    simple::matrix<int> _mrx = {
        { 1, 2, 3 },
        { 3, 4, 5 },
        { 5, 6, 7 } };
    simple::matrix<int> _actual = _mrx.submatrix(1, 1);
    simple::matrix<int> _expected = {
        { 1, 3 },
        { 5, 7 } };
    REQUIRE(_expected == _actual);
}

TEST_CASE("minor matrix", "[minor_matrix]") {
    simple::matrix<int> _mrx = {
        { 1, 2 },
        { 3, 4 },
        { 5, 6 } };
    REQUIRE_THROWS(_mrx.minor_matrix());
    _mrx = {
        { 1, 2, 3 },
        { 3, 4, 5 },
        { 5, 6, 7 } };
    simple::matrix<int> _actual = _mrx.minor_matrix();
    simple::matrix<int> _expected = {
        { -2, -4, -2 },
        { -4, -8, -4 },
        { -2, -4, -2 } };
    REQUIRE(_expected == _actual);
}

TEST_CASE("trace matrix", "[trace]") {
    simple::matrix<int> _mrx = {
        { 1, 2 },
        { 3, 4 },
        { 5, 6 } };
    REQUIRE_THROWS(_mrx.trace());
    _mrx = {
        { 1, 2, 3 },
        { 3, 4, 5 },
        { 5, 6, 7 } };
    REQUIRE(_mrx.trace() == 12);
}

TEST_CASE("minor determinant matrix", "[minor_determinant]") {
    simple::matrix<int> _mrx = {
        { 1, 2 },
        { 3, 4 },
        { 5, 6 } };
    REQUIRE_THROWS(_mrx.minor_determinant(0, 0));
    _mrx = { { 1 } };
    REQUIRE_THROWS(_mrx.minor_determinant(0, 0));
    _mrx = {
        { 1, 2, 3 },
        { 3, 4, 5 },
        { 5, 6, 7 } };
    int _actual = _mrx.minor_determinant(0, 0);
    int _expected = 4 * 7 - 6 * 5;
    REQUIRE(_expected == _actual);
}

TEST_CASE("cofactor", "[cofactor]") {
    simple::matrix<int> _mrx = {
        { 1, 2, 3 },
        { 3, 4, 5 },
        { 5, 6, 7 } };
    int _actual = _mrx.cofactor(1, 1);
    int _expected = pow(-1, 1 + 1) * (1 * 7 - 5 * 3);
    REQUIRE(_expected == _actual);

    _actual = _mrx.cofactor(2, 1);
    _expected = pow(-1, 2 + 1) * (1 * 5 - 3 * 3);
    REQUIRE(_expected == _actual);
}

TEST_CASE("determinant", "[determinant]") {
    simple::matrix<int> _mrx = {
        { 1, 2 },
        { 3, 4 },
        { 5, 6 } };
    REQUIRE_THROWS(_mrx.determinant());
    _mrx = {
        { 5, 4, 3 },
        { 1, 2, 3 },
        { 6, 4, 5 } };
    int _actual = _mrx.determinant();
    int _expected
        = 5 * 2 * 5
        + 1 * 4 * 3
        + 4 * 3 * 6
        - 6 * 2 * 3
        - 4 * 3 * 5
        - 1 * 4 * 5;
    REQUIRE(_expected == _actual);
}

TEST_CASE("printing a matrix to the console", "[operator<<] [pretty]") {
    simple::matrix<int> _mtx1 = {
        { 5, 4, 3 },
        { 1, 2, 3 },
        { 6, 4, 5 } };
    std::ostringstream _ostream;
    _ostream << _mtx1;
    using Catch::Matchers::Equals;
    REQUIRE_THAT(
        _ostream.str(), Equals(
            "┌─         ─┐\n"
            "│  5  4  3  │\n"
            "│  1  2  3  │\n"
            "│  6  4  5  │\n"
            "└─         ─┘"
        )
    );
}

TEST_CASE("matrix addition", "[operator+=] [operator+]") {
    simple::matrix<int> _mtx1 = {
        { 5, 4, 3 },
        { 1, 2, 3 },
        { 6, 4, 5 } };
    simple::matrix<int> _mtx2 = {
        { 7, 8, 5 },
        { 6, 9, 2 },
        { 3, 6, 6 } };
    simple::matrix<int> _actual = _mtx1 + _mtx2;
    simple::matrix<int> _expected = {
        { 12, 12, 8  },
        {  7, 11, 5  },
        {  9, 10, 11 } };
    REQUIRE(_expected == _actual);
    simple::matrix<int> _mtx2 = {
        { 7, 8, 5 },
        { 6, 9, 2 },
        { 3, 6, 6 },
        { 4, 3, 9 } };
    REQUIRE_THROWS(_mtx1 + _mtx2);
}

TEST_CASE("matrix subtraction", "[operator-=] [operator-]") {
    simple::matrix<int> _mtx1 = {
        { 5, 4, 3 },
        { 1, 2, 3 },
        { 6, 4, 5 } };
    simple::matrix<int> _mtx2 = {
        { 7, 8, 5 },
        { 6, 9, 2 },
        { 3, 6, 6 } };
    simple::matrix<int> _actual = _mtx1 - _mtx2;
    simple::matrix<int> _expected = {
        { -2, -4, -2 },
        { -5, -7,  1 },
        {  3, -2, -1 } };
    REQUIRE(_expected == _actual);
    simple::matrix<int> _mtx2 = {
        { 7, 8, 5 },
        { 6, 9, 2 },
        { 3, 6, 6 },
        { 4, 3, 9 } };
    REQUIRE_THROWS(_mtx1 - _mtx2);
}

TEST_CASE("matrix multiplication", "[operator*=] [operator*]") {
    simple::matrix<int> _mtx1 = {
        { 5, 4, 3 },
        { 1, 2, 3 },
        { 6, 4, 5 } };
    simple::matrix<int> _mtx2 = {
        { 7, 8, 5 },
        { 6, 3, 2 },
        { 3, 6, 6 } };
    simple::matrix<int> _actual = _mtx1 * _mtx2;
    simple::matrix<int> _expected = {
        { 68, 70, 51 },
        { 28, 32, 27 },
        { 81, 90, 68 } };
    REQUIRE(_expected == _actual);
    _mtx1 = {
        { 1, 3, 5 },
        { 3, 2, 8 },
        { 9, 4, 2 },
        { 4, 8, 1 } };
    _mtx2 = {
        { 3, 4 },
        { 2, 6 },
        { 1, 7 } };
    _actual = _mtx1 * _mtx2;
    _expected = {
        { 14, 57 },
        { 21, 80 },
        { 37, 74 },
        { 29, 71 } };
    REQUIRE(_actual.size_rows() == 4);
    REQUIRE(_actual.size_collumns() == 2);
    REQUIRE(_expected == _actual);
    _mtx2 = {
        { 3, 4 },
        { 2, 6 },
        { 6, 3 },
        { 1, 7 } };
    REQUIRE_THROWS(_mtx1 * _mtx2);
}
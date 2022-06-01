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

// TEST_CASE("minor matrix", "[minor_matrix]") {
//     simple::matrix<int> _mrx = {
//         { 1, 2 },
//         { 3, 4 },
//         { 5, 6 } };
//     REQUIRE_THROWS(_mrx.minor_matrix());
//     _mrx = {
//         { 1, 2, 3 },
//         { 3, 4, 5 },
//         { 5, 6, 7 } };
//     simple::matrix<int> _actual = _mrx.minor_matrix();
//     simple::matrix<int> _expected = {
//         { -2, -4, -2 },
//         { -4, -8, -4 },
//         { -2, -4, -2 } };
//     REQUIRE(_expected == _actual);
// }

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


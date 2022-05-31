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
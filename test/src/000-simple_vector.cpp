#include "catch2/catch.hpp"
#include "simple_vector.hpp"

TEST_CASE("norm of the vector", "[norm]") {
    simple::vector<int> _vec1 = { 1, 2, 3, 4, 5 };

    using namespace Catch::literals;
    REQUIRE(_vec1.norm() == 7.416198487095663_a);

    _vec1 = { 0, 0, 0 };
    REQUIRE(_vec1.norm() == 0_a);

    simple::vector<double> _vec2 = { -3, 2.5, 15, 10.25, 2, 2.225 };
    REQUIRE(_vec2.norm() == 18.8218788913328_a);

    _vec2.clear();
    REQUIRE(_vec2.norm() == 0_a);
}
#include "catch2/catch.hpp"
#include "simple_vector.hpp"


TEST_CASE("norm of the vector", "[norm]") {
    simple::vector<int> _vec = { 1, 2, 3, 4, 5 };

    using namespace Catch::literals;
    REQUIRE(_vec.norm() == 7.416198487095663_a);
}
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

TEST_CASE("reading a vector from a file", "[read]") {
    simple::vector<int> _vec1;
    simple::read(_vec1, std::string { "file/read_back_inserter.txt" });
    using Catch::Matchers::Equals;
    REQUIRE_THAT(_vec1, Equals<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 }));
}

TEST_CASE("the file does not exist", "[read]") {
    simple::vector<int> _vec1;
    REQUIRE_THROWS(simple::read(_vec1, std::string { "failed.txt" }));
}

TEST_CASE("reading a vector multiple numbers from a file", "[read]") {
    simple::vector<int> _vec1;
    simple::read(_vec1, std::string { "file/read_back_inserter.txt" }, 5);
    using Catch::Matchers::Equals;
    REQUIRE_THAT(_vec1, Equals<int>({ 1, 2, 3, 4, 5 }));
}

TEST_CASE("there are not so many numbers in the file", "[read]") {
    simple::vector<int> _vec1;
    REQUIRE_THROWS(simple::read(_vec1, std::string { "file/read_back_inserter.txt" }, 100));
}
project(unit_tests LANGUAGES CXX)

set(SOURCES_TEST_FILE src/000-simple_vector.cpp)

add_executable(unit_tests ${SOURCES_TEST_FILE})

target_link_libraries(unit_tests
    simple::matrix
    Catch2::Catch2
    Catch2::Catch2WithMain)
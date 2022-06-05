project(unit_tests LANGUAGES CXX)

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/test_benchmark_data.hpp
"#define TEST_DATA_DIRECTORY \"${CMAKE_CURRENT_SOURCE_DIR}\"")

set(SOURCES_TEST_FILE
    src/000-simple_vector.cpp
    src/001-simple_matrix.cpp)

add_executable(unit_tests ${SOURCES_TEST_FILE})

target_link_libraries(unit_tests
    simple::matrix
    Catch2::Catch2
    Catch2::Catch2WithMain)
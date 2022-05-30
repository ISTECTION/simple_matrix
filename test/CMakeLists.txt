project(unit_tests LANGUAGES CXX)

add_custom_command(TARGET unit_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/file
            ${CMAKE_CURRENT_BINARY_DIR}/file)

set(SOURCES_TEST_FILE src/000-simple_vector.cpp)

add_executable(unit_tests ${SOURCES_TEST_FILE})

target_link_libraries(unit_tests
    simple::matrix
    Catch2::Catch2
    Catch2::Catch2WithMain)
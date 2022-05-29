cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)
set(SIMPLE_MATRIX_PROJECT_NAME    "simple_matrix")
# ------------------------------------------------------------------------------
string(MAKE_C_IDENTIFIER ${SIMPLE_MATRIX_PROJECT_NAME} SIMPLE_MATRIX_PROJECT_ID)
string(TOUPPER           ${SIMPLE_MATRIX_PROJECT_NAME} SIMPLE_MATRIX_PROJECT_ID)
# ------------------------------------------------------------------------------
project(${SIMPLE_MATRIX_PROJECT_NAME}
    DESCRIPTION     "algebraic functions for matrix and vector"
    HOMEPAGE_URL    "https://github.com/ISTECTION/simple_matrix"
    LANGUAGES CXX)
# ------------------------------------------------------------------------------
add_library(${PROJECT_NAME} INTERFACE)
add_library(simple::matrix ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)
#-------------------------------------------------------------------------------
set(SIMPLE_MATRIX_EXECUTABLE    "simple_run")

add_executable(${SIMPLE_MATRIX_EXECUTABLE} src/main.cpp)

target_link_libraries(${SIMPLE_MATRIX_EXECUTABLE} PRIVATE ${PROJECT_NAME})
#---------------------------------- Опции --------------------------------------
option(SIMPLE_MATRIX_TEST "Включить тестирование Catch2" OFF)
#-------------------------------------------------------------------------------
if(SIMPLE_MATRIX_TEST)
    enable_testing()
    message(STATUS "Тестирование проекта ${PROJECT_NAME} включено (Catch2)")
    set(CATCH_BUILD_STATIC_LIBRARY ON CACHE BOOL "static ALIAS Catch2::Catch2WithMain" FORCE)
    add_subdirectory(vendor/Catch2)
    add_subdirectory(test)
endif()
# ---------------------------- Подведение итогов -------------------------------
message(STATUS "===== Окончательный обзор для ${PROJECT_NAME} =====")
message(STATUS "  GitHub:     ${CMAKE_PROJECT_HOMEPAGE_URL}")
message(STATUS "  Version:    1.0.0")
message(STATUS "  Compiler:   ${CMAKE_CXX_COMPILER}")
# ------------------------------------------------------------------------------
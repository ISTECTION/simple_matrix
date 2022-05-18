cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)
set(SIMPLE_MATRIX_PROJECT_NAME    "simple_matrix")

string(MAKE_C_IDENTIFIER ${SIMPLE_MATRIX_PROJECT_NAME} SIMPLE_MATRIX_PROJECT_ID)
string(TOUPPER           ${SIMPLE_MATRIX_PROJECT_NAME} SIMPLE_MATRIX_PROJECT_ID)


project(${SIMPLE_MATRIX_PROJECT_NAME}
    DESCRIPTION     "algebraic functions for matrix and vector"
    HOMEPAGE_URL    "https://github.com/ISTECTION/simple_matrix"
    LANGUAGES CXX)

# ----------------------------- Подведение итогов ------------------------------
message(STATUS "===== Окончательный обзор для ${PROJECT_NAME} =====")
message(STATUS "  GitHub:     ${CMAKE_PROJECT_HOMEPAGE_URL}")
message(STATUS "  Version:    0.0.1")
message(STATUS "  Compiler:   ${CMAKE_CXX_COMPILER}")
# ------------------------------------------------------------------------------
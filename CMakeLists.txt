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

if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 19.12.25835)
    set(CMAKE_CXX20_STANDARD_COMPILE_OPTION  "-std:c++latest")
    set(CMAKE_CXX20_EXTENSION_COMPILE_OPTION "-std:c++latest")
endif()
#---------------------------------- Модули -------------------------------------
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/module" ${CMAKE_MODULE_PATH})

find_package(GitInfo)

git_version_info(${SIMPLE_MATRIX_PROJECT_ID})
#---------------------------------- Опции --------------------------------------
option(SIMPLE_MATRIX_TEST "Включить тестирование Catch2" OFF)
option(SIMPLE_MATRIX_DOC  "Включить тестирование Catch2" OFF)
#-------------------------------------------------------------------------------
if(SIMPLE_MATRIX_TEST)
    enable_testing()
    message(STATUS "Тестирование проекта ${PROJECT_NAME} включено (Catch2)")
    set(CATCH_BUILD_STATIC_LIBRARY ON CACHE BOOL "static ALIAS Catch2::Catch2WithMain" FORCE)
    add_subdirectory(vendor/Catch2)
    add_subdirectory(test)
endif()

if(SIMPLE_MATRIX_DOC)
    find_package(Doxygen REQUIRED)
    if(DOXYGEN_FOUND)
        set(DOXYGEN_PROJECT_NAME   ${PROJECT_NAME})
        set(DOXYGEN_PROJECT_BRIEF  "operations with vectors and matrices")
        set(DOXYGEN_PROJECT_NUMBER ${SIMPLE_MATRIX_VERSION})

        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.doxygen.in Doxyfile.doxygen @ONLY)
        file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/docs/styles DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

        add_custom_command(
            OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.doxygen
            COMMENT "Documentation generation")
        add_custom_target(docs ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/docs)

        file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/docs/Documentation.html
            "<meta http-equiv=\"refresh\" content=\"0; url=${CMAKE_CURRENT_BINARY_DIR}/docs/html/index.html\">")
    else()
        message(STATUS "Исполняемый файл doxygen не был найден")
    endif()
endif()
# ---------------------------- Подведение итогов -------------------------------
message(STATUS "===== Окончательный обзор для ${PROJECT_NAME} =====")
message(STATUS "  GitHub:     ${CMAKE_PROJECT_HOMEPAGE_URL}")
message(STATUS "  Version:    ${SIMPLE_MATRIX_VERSION}")
message(STATUS "  Compiler:   ${CMAKE_CXX_COMPILER}")
message(STATUS "============ Дополнительная информация ============")
message(STATUS "  Doxygen:    ${DOXYGEN_VERSION}")
# ------------------------------------------------------------------------------
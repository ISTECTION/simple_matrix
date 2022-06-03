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
#-------------------------------------------------------------------------------
set(SIMPLE_MATRIX_EXECUTABLE "simple_run")

add_executable(${SIMPLE_MATRIX_EXECUTABLE} src/main.cpp)

target_link_libraries(${SIMPLE_MATRIX_EXECUTABLE} PRIVATE ${PROJECT_NAME})
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
        set(SIMPLE_MATRIX_HEADERS
            ${CMAKE_CURRENT_SOURCE_DIR}/include/exception/exception.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/utils/lightweight.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/simple_vector.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/simple_matrix.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/common.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

        set(DOXYGEN_PROJECT_NUMBER ${SIMPLE_MATRIX_VERSION})
        set(DOXYGEN_PROJECT_BRIEF "operations with vectors and matrices")
        set(DOXYGEN_PROJECT_LOGO "${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen-custom/matrix.svg")
        set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs)
        set(DOXYGEN_CREATE_SUBDIRS YES)
        set(DOXYGEN_OUTPUT_LANGUAGE Russian)
        set(DOXYGEN_INLINE_INHERITED_MEMB YES)
        set(DOXYGEN_STRIP_FROM_PATH ${CMAKE_CURRENT_SOURCE_DIR})
        set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
        set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
        set(DOXYGEN_GENERATE_TREEVIEW YES)
        set(DOXYGEN_HAVE_DOT YES)
        set(DOXYGEN_DOT_IMAGE_FORMAT svg)
        set(DOXYGEN_DOT_TRANSPARENT YES)
        set(DOXYGEN_EXTRACT_ALL YES)
        set(DOXYGEN_RECURSIVE NO)
        set(DOXYGEN_ENABLE_PREPROCESSING NO)

        set(DOXYGEN_HTML_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen-custom/header.html)
        set(DOXYGEN_HTML_EXTRA_STYLESHEET
            ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen-awesome.css
            ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen-custom/custom.css
            ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen-awesome-sidebar-only.css
            ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen-awesome-sidebar-only-darkmode-toggle.css
            ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen-custom/custom-alternative.css)
        set(DOXYGEN_HTML_EXTRA_FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen-awesome-darkmode-toggle.js
            ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen-awesome-fragment-copy-button.js
            ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen-awesome-paragraph-link.js
            ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen-custom/toggle-alternative-theme.js)

        set(DOXYGEN_HTML_COLORSTYLE_HUE 209)
        set(DOXYGEN_HTML_COLORSTYLE_SAT 255)
        set(DOXYGEN_HTML_COLORSTYLE_GAMMA 113)


        doxygen_add_docs(doxygen ${SIMPLE_MATRIX_HEADERS})
        add_custom_command(
            OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.doxygen
            COMMENT "Documentation generation")
        add_custom_target(docs ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/docs)
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
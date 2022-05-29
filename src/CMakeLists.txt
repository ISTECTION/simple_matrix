add_library(${PROJECT_NAME} INTERFACE)
add_library(simple::matrix ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)
#-------------------------------------------------------------------------------
set(SIMPLE_MATRIX_EXECUTABLE    "simple_run")

add_executable(${SIMPLE_MATRIX_EXECUTABLE} main.cpp)

target_link_libraries(${SIMPLE_MATRIX_EXECUTABLE} PRIVATE ${PROJECT_NAME})
#------------------------------- Опции -----------------------------------------
option(SIMPLE_MARTIX_TEST "Включить тестирование Catch2" OFF)  # Catch2
#-------------------------------------------------------------------------------
if(SIMPLE_MARTIX_TEST)
    enable_testing()
    message(STATUS "Тестирование проекта ${PROJECT_NAME} включено (Catch2)")
    add_subdirectory(test)
endif()
add_executable(${PROJECT_NAME}
    main.cpp
    simple_vector.cpp
    simple_matrix.cpp)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include)
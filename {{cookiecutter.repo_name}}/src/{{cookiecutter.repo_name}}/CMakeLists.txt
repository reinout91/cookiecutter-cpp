add_library(matrix_example_utils matrix_example_utils.cpp)
add_executable(main main.cpp)
target_link_libraries(main matrix_example_utils fmt::fmt ${ARMADILLO_LIBRARIES})

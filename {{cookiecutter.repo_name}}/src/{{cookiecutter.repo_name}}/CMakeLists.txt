add_library(matrix_example_utils matrix_example_utils.cpp)
add_executable(${exename} main.cpp)
target_link_libraries(main matrix_example_utils fmt::fmt ${ARMADILLO_LIBRARIES})

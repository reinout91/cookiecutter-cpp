# Set compile options
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set_target_properties (${exename} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)
if (MSVC)
  target_compile_options ({{ cookiecutter.project_name }} PRIVATE /W4 /WX /utf-8)
else ()
  target_compile_options ({{ cookiecutter.project_name }} PRIVATE -pedantic -Wall -Wextra -Wshadow -Werror)
endif ()


add_library(matrix_example_utils matrix_example_utils.cpp)
add_executable({{ cookiecutter.project_name }} main.cpp)
target_link_libraries({{ cookiecutter.project_name }} matrix_example_utils fmt::fmt ${ARMADILLO_LIBRARIES})

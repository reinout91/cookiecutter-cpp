# set(CMAKE_INCLUDE_CURRENT_DIR ON)
set (exename "{{ cookiecutter.project_name }}")
add_library({{ cookiecutter.project_name }}_utils {{ cookiecutter.project_name }}_utils.cpp)
add_executable(${exename} {{ cookiecutter.project_name }}.cpp)
target_compile_features ({{ cookiecutter.project_name }}_utils INTERFACE cxx_std_14)

target_compile_options(${exename}
  PRIVATE
    ${_CXX_FLAGS}
  )

# Set compile options
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set_target_properties (${exename} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)
if (MSVC)
  target_compile_options (${exename}} PRIVATE /W4 /WX /utf-8)
else ()
  target_compile_options (${exename} PRIVATE -pedantic -Wall -Wextra -Wshadow -Werror)
endif ()

target_link_libraries(${exename} {{ cookiecutter.project_name }}_utils PRIVATE fmt::fmt ${ARMADILLO_LIBRARIES})

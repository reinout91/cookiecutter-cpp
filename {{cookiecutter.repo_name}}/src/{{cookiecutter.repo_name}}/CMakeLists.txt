add_library({{cookiecutter.repo_name}}Utils STATIC {{cookiecutter.repo_name}}Utils.cpp)
include_directories(${ARMADILLO_INCLUDE_DIRS})
add_executable({{cookiecutter.repo_name}} {{cookiecutter.repo_name}}.cpp)
target_link_libraries({{cookiecutter.repo_name}} {{cookiecutter.repo_name}}Utils fmt::fmt ${ARMADILLO_LIBRARIES})

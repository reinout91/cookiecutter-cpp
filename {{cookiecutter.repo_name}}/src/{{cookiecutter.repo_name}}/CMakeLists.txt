add_library({{cookiecutter.repo_name}}Utils STATIC {{cookiecutter.repo_name}}Utils.cpp)
add_executable({{cookiecutter.repo_name}} {{cookiecutter.repo_name}}.cpp)
target_link_libraries({{cookiecutter.repo_name}} PRIVATE {{cookiecutter.repo_name}}Utils fmt::fmt ${ARMADILLO_LIBRARIES})

add_library({{cookiecutter.repo_name}}_utils {{cookiecutter.repo_name}}_utils.cpp)
add_executable(main main.cpp)
target_link_libraries(main {{cookiecutter.repo_name}}_utils fmt::fmt)

# Target:   {{ cookiecutter.project_name }}
add_subdirectory({{ cookiecutter.project_name }})

# add executable main
add_executable(main main.cpp)
# tell the linker to bin these objects:
# target_link_libraries(main)

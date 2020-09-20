# {{ cookiecutter.project_name }}
# {{ cookiecutter.description }}
# Copyright {{ cookiecutter.year }}, {{ cookiecutter.author }}
cmake_minimum_required (VERSION 3.8.0 FATAL_ERROR)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project
cmake_minimum_required (VERSION 3.8.0 FATAL_ERROR)
project({{cookiecutter.repo_name}}
  VERSION {{ cookiecutter.version }}
  LANGUAGES CXX
  PROJECT_DESCRIPTION   "{{ cookiecutter.description }}"
  PROJECT_AUTHOR        "{{ cookiecutter.author }}"
  PROJECT_URL           "https://github.com/{{ cookiecutter.username }}/{{ cookiecutter.repo_name }}"
) 

# require C++17
target_compile_features ({{cookiecutter.repo_name}} INTERFACE cxx_std_17)

# Build flags
# Set build type if not set.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# testing
enable_testing ()
option ({{ cookiecutter.project_name|upper }}_BUILD_TESTS "Build test programs" ON)
if ({{ cookiecutter.project_name|upper }}_BUILD_TESTS)
  add_subdirectory (test)
endif ()

# install and export target
install (TARGETS {{ cookiecutter.project_name|lower }} EXPORT {{ cookiecutter.project_name|lower }}-targets)

install (EXPORT {{ cookiecutter.project_name }}-targets
  FILE {{ cookiecutter.project_name|lower }}-config.cmake
  NAMESPACE {{ cookiecutter.project_name+'::' }}
  DESTINATION ${% raw %}{{% endraw %}{{ cookiecutter.project_name|upper}}{% raw %}_INSTALL_CMAKE_DIR}{% endraw %}
  )
  
install (DIRECTORY include/ DESTINATION ${% raw %}{{% endraw %}{{ cookiecutter.project_name|upper }}{% raw %}_INSTALL_INCLUDE_DIR)}{% endraw %}
install (FILES LICENSE DESTINATION ${% raw %}{{% endraw %}{{ cookiecutter.project_name|upper }}{% raw %}_INSTALL_DOC_DIR)}{% endraw %}

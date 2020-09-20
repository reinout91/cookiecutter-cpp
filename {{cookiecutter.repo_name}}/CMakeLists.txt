# {{ cookiecutter.project_name }}
# {{ cookiecutter.description }}
# Copyright {{ cookiecutter.year }}, {{ cookiecutter.author }}
cmake_minimum_required (VERSION 3.8.0 FATAL_ERROR)

# installation directories
set ({{ cookiecutter.project_name|upper }}_INSTALL_INCLUDE_DIR "lib" CACHE STRING "The installation include directory")
set ({{ cookiecutter.project_name|upper }}_INSTALL_DOC_DIR "doc" CACHE STRING "The installation doc directory")
set ({{ cookiecutter.project_name|upper }}_INSTALL_CMAKE_DIR "share/{{ cookiecutter.project_name|lower }}/cmake" CACHE STRING "The installation cmake directory")

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib) # Static link libraries
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) # Executables
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib) # Dynamic link libraries

# Make flags for running from an editor
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
target_compile_features ({{cookiecutter.repo_name}} INTERFACE cxx_std_14)

# Set build type if not set.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Set compile options
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set_target_properties (${exename} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)
if (MSVC)
  target_compile_options (${exename} PRIVATE /W4 /WX /utf-8)
else ()
  target_compile_options (${exename} PRIVATE -pedantic -Wall -Wextra -Wshadow -Werror)
endif ()

# Add the project package called {{ cookiecutter.project_name|upper }}
add_subdirectory (src/{{ cookiecutter.project_name|upper }})

# testing
enable_testing ()
option ({{ cookiecutter.project_name|upper }}_BUILD_TESTS "Build test programs" ON)
if ({{ cookiecutter.project_name|upper }}_BUILD_TESTS)
  add_subdirectory (test)
endif ()

# Doxygen documentation
add_subdirectory(doc)

# install and export target
install (TARGETS {{ cookiecutter.project_name|lower }} EXPORT {{ cookiecutter.project_name|lower }}-targets)

install (EXPORT {{ cookiecutter.project_name }}-targets
  FILE {{ cookiecutter.project_name|lower }}-config.cmake
  NAMESPACE {{ cookiecutter.project_name+'::' }}
  DESTINATION ${% raw %}{{% endraw %}{{ cookiecutter.project_name|upper}}{% raw %}_INSTALL_CMAKE_DIR}{% endraw %}
  )
  
install (DIRECTORY lib/ DESTINATION ${% raw %}{{% endraw %}{{ cookiecutter.project_name|upper }}{% raw %}_INSTALL_INCLUDE_DIR}){% endraw %}
install (FILES LICENSE DESTINATION ${% raw %}{{% endraw %}{{ cookiecutter.project_name|upper }}{% raw %}_INSTALL_DOC_DIR}){% endraw %}

# Package manager manager (fmt is just a sample library to test the manager)
include(pmm.cmake)
pmm(
  # Use vcpkg
  VCPKG
  # Specify vcpkg branch, tag, or revision
  REVISION master
  # Space seperated list of required vcpkg packages
  REQUIRES fmt
)

# Find required packages for project
find_package(fmt CONFIG REQUIRED)
find_package(Armadillo REQUIRED) #install it using ubuntu package manager:  sudo apt-get install libarmadillo-dev

# TODO: Stick to https://cliutils.gitlab.io/modern-cmake/chapters/intro/dodonot.html
# {{ cookiecutter.project_name }}
# {{ cookiecutter.description }}
# Copyright {{ cookiecutter.year }}, {{ cookiecutter.author }}
cmake_minimum_required(VERSION 3.2)

# can be useful for vim?
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project
project({{ cookiecutter.project_name }} C CXX)
set(PROJECT_DESCRIPTION   "{{ cookiecutter.description }}")
set(PROJECT_AUTHOR        "{{ cookiecutter.author }}")
set(PROJECT_URL           "https://github.com/{{ cookiecutter.username }}/{{ cookiecutter.repo_name }}")
set(PROJECT_VERSION_MAJOR "{{ cookiecutter.version.split('.')[0] }}")
set(PROJECT_VERSION_MINOR "{{ cookiecutter.version.split('.')[1] }}")
set(PROJECT_VERSION_PATCH "{{ cookiecutter.version.split('.')[2] }}")

# Build flags
# Set build type if not set.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")
{% if cookiecutter.pedantic -%}
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")
{%- endif %}

# Tell cmake to output binaries here:
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib) # Static link libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) # Executables
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib) # Dynamic link libraries

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

# ---------------------------------------------------------
# Features
# ---------------------------------------------------------
add_subdirectory(external)
# Tell cmake where to look for *.h files.
include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/src/{{cookiecutter.repo_name}})
# Outsource the actual processing to folders.
add_subdirectory(src)
# Must be in the top-most CMakeLists.txt file.
enable_testing()
# Outsource tests to another folder.
add_subdirectory(test)
add_subdirectory(doc)

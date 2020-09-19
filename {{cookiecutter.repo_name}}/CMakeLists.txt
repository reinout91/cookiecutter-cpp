# matrix_example
# A rock solid project with enforced style, testing and static analysis
# Copyright 2020, First Last
cmake_minimum_required(VERSION 3.2)

# can be useful for vim?
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project
project(matrix_example C CXX)
set(PROJECT_DESCRIPTION   "A rock solid project with enforced style, testing and static analysis")
set(PROJECT_AUTHOR        "First Last")
set(PROJECT_URL           "https://github.com/flast/matrix_example")
set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "1")

# Build flags
# Set build type if not set.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

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
find_package(Armadillo REQUIRED) #install it using ubuntu package manager:  sudo apt-get install libarmadillo-dev

# ---------------------------------------------------------
# Features
# ---------------------------------------------------------
add_subdirectory(external)
# Tell cmake where to look for *.h files.
include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/src/matrix_example )
# Outsource the actual processing to folders.
add_subdirectory(src)
# Must be in the top-most CMakeLists.txt file.
enable_testing()
# Outsource tests to another folder.
add_subdirectory(test)
add_subdirectory(doc)

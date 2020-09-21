# {{ cookiecutter.project_name }}
# {{ cookiecutter.description }}
# Copyright {{ cookiecutter.year }}, {{ cookiecutter.author }}
cmake_minimum_required (VERSION 3.8.0 FATAL_ERROR)

# Check compiler support for vectorization
# include(CheckCXXCompilerFlag)
# check_cxx_compiler_flag("-march=native" _march_native_works)
# check_cxx_compiler_flag("-xHost" _xhost_works)

# installation directories
# set ({{ cookiecutter.project_name|upper }}_INSTALL_INCLUDE_DIR "lib" CACHE STRING "The installation include directory")
# set ({{ cookiecutter.project_name|upper }}_INSTALL_DOC_DIR "doc" CACHE STRING "The installation doc directory")
# set ({{ cookiecutter.project_name|upper }}_INSTALL_CMAKE_DIR "share/{{ cookiecutter.project_name|lower }}/cmake" CACHE STRING "The installation cmake directory")

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib) # Static link libraries
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) # Executables
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib) # Dynamic link libraries

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR} CACHE PATH "Installation directory for libraries")
set(INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR} CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR} CACHE PATH "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKEDIR CMake)
else()
  set(DEF_INSTALL_CMAKEDIR share/cmake/${PROJECT_NAME})
endif()
set(INSTALL_CMAKEDIR ${DEF_INSTALL_CMAKEDIR} CACHE PATH "Installation directory for CMake files")

# Make flags for running from an editor
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project
project({{cookiecutter.repo_name}} VERSION {{ cookiecutter.version }} LANGUAGES CXX)
set(PROJECT_DESCRIPTION   "A rock solid project with enforced style, testing and static analysis")
set(PROJECT_AUTHOR        "First Last")
set(PROJECT_URL           "https://github.com/flast/matrix_example")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Project will be installed to ${CMAKE_INSTALL_PREFIX}")

# Set build type if not set.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type set to ${CMAKE_BUILD_TYPE}")

# Add the project package called {{ cookiecutter.project_name }}
add_subdirectory (src/{{ cookiecutter.project_name|lower }})

# add external
add_subdirectory(external)

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

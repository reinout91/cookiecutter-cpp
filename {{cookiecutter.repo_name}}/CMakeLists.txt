  
# {{ cookiecutter.project_name }}
# {{ cookiecutter.description }}
# Copyright {{ cookiecutter.year }}, {{ cookiecutter.author }}
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Can be useful for vim?
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project
project({{cookiecutter.project_name}} C CXX)
project({{cookiecutter.repo_name}} VERSION {{ cookiecutter.version }} LANGUAGES CXX)
set(PROJECT_DESCRIPTION   "{{ cookiecutter.description }}")
set(PROJECT_AUTHOR        "{{ cookiecutter.author }}")
set(PROJECT_URL           "https://github.com/{{ cookiecutter.username }}/{{ cookiecutter.repo_name }}")

# Build flags
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set (CMAKE_CXX_STANDARD 14)

if (MSVC)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /utf-8")
else ()
  set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")
endif ()

# Tell cmake to output binaries here:
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib) # Static link libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) # Executables
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib) # Dynamic link libraries

include(pmm.cmake)

# In the case of a Microsoft system, all packages should be installed by VCPKG, for UNIX systems, the user has to install the required packages using their system package manager.
# In Linux, when a broken VCPKG package is installed by VCPKG, it should be manually uninstalled. Otherwise build errors might occur.

set(BUILD_SHARED_LIBS=false)

if (MSVC)
  set(PMM_PACKAGES fmt openblas lapack armadillo)
else ()
  set(PMM_PACKAGES fmt openblas lapack armadillo)
  #sudo apt-get install libarmadillo-dev (VCPKG version is broken)
endif ()
pmm(
  # Use vcpkg
  VCPKG
  # Specify vcpkg branch, tag, or revision
  REVISION master
  # Space seperated list of required vcpkg packages
  REQUIRES ${PMM_PACKAGES}
)

# Find required packages for project, these are the cmake targets reported by vcpkg.
find_package(fmt CONFIG REQUIRED)
find_package(LAPACK)
find_package(OpenBLAS CONFIG REQUIRED)
find_package(Armadillo REQUIRED)

#include_directories(${ARMADILLO_INCLUDE_DIRS})

add_subdirectory(external)
# Tell cmake where to look for *.h files.
include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/src/{{cookiecutter.project_name}} )
# Outsource the actual processing to folders.
add_subdirectory(src)

# Must be in the top-most CMakeLists.txt file.
# testing
enable_testing ()
option ({{ cookiecutter.project_name|upper }}_BUILD_TESTS "Build test programs" ON)
if ({{ cookiecutter.project_name|upper }}_BUILD_TESTS)
  add_subdirectory (test)
endif ()



add_subdirectory(doc)

# Prepare RPATH
if (NOT MSVC)
  set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local") #We don't want to install to the default /usr/local. 
endif ()
file(RELATIVE_PATH _rel ${CMAKE_INSTALL_PREFIX}/${INSTALL_BINDIR} ${CMAKE_INSTALL_PREFIX})
if(APPLE)
  set(_rpath "@loader_path/${_rel}")
else()
  set(_rpath "\$ORIGIN/${_rel}")
endif()
file(TO_NATIVE_PATH "${_rpath}/${INSTALL_LIBDIR}" message_RPATH)

set_target_properties({{cookiecutter.project_name}}
  PROPERTIES
    MACOSX_RPATH ON
    SKIP_BUILD_RPATH OFF
    BUILD_WITH_INSTALL_RPATH OFF
    INSTALL_RPATH "${message_RPATH}"
    INSTALL_RPATH_USE_LINK_PATH ON
  )

# Here you can select the binaries and libraries that have to be installed to the system.
message(STATUS "Project will be installed to ${CMAKE_INSTALL_PREFIX}, admin rights may be required to make install")
install(
  TARGETS
    {{cookiecutter.repo_name}}Utils
    {{cookiecutter.repo_name}}
  ARCHIVE
  DESTINATION ${INSTALL_LIBDIR}
    COMPONENT ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
  RUNTIME
    DESTINATION ${INSTALL_BINDIR}
    COMPONENT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  LIBRARY
    DESTINATION ${INSTALL_LIBDIR}
    COMPONENT ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
  PUBLIC_HEADER
    DESTINATION ${INSTALL_INCLUDEDIR}/tythUtils
    COMPONENT dev
  )

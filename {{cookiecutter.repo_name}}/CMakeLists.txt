# {{cookiecutter.project_name}}
# A rock solid project with enforced style, testing and static analysis
# Copyright 2020, First Last
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Can be useful for vim?
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project
project({{cookiecutter.project_name}} C CXX)
project({{cookiecutter.repo_name}} VERSION {{ cookiecutter.version }} LANGUAGES CXX)
set(PROJECT_DESCRIPTION   "A rock solid project with enforced style, testing and static analysis")
set(PROJECT_AUTHOR        "First Last")
set(PROJECT_URL           "https://github.com/flast/{{cookiecutter.project_name}}")

# Build flags
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set (CMAKE_CXX_STANDARD 14)

if (MSVC)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /utf-8")
else ()
  set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORYCMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
# Package manager manager (fmt is just a sample library to test the manager)
include(pmm.cmake)

# In the case of a Microsoft system, all packages should be installed by VCPKG, for UNIX systems, the user has to install the required packages using their system package manager.
if (MSVC)
  set(PMM_PACKAGES "fmt Armadillo")
else ()
  set(PMM_PACKAGES "fmt")
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
find_package(Armadillo REQUIRED)

add_subdirectory(external)
# Tell cmake where to look for *.h files.
include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/src/{{cookiecutter.project_name}} )
# Outsource the actual processing to folders.
add_subdirectory(src)
# Must be in the top-most CMakeLists.txt file.
enable_testing()
# Outsource tests to another folder.
add_subdirectory(test)
add_subdirectory(doc)

# Prepare RPATH
if (NOT MSVC)
  set(CMAKE_INSTALL_PREFIX "/home/user/.local") #We don't want to install to the default /usr/local. 
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
    {{cookiecutter.project_name}}_utils
    {{cookiecutter.project_name}}
  ARCHIVE
    DESTINATION ${INSTALL_LIBDIR}
    COMPONENT lib
  RUNTIME
    DESTINATION ${INSTALL_BINDIR}
    COMPONENT bin
  LIBRARY
    DESTINATION ${INSTALL_LIBDIR}
    COMPONENT lib
  PUBLIC_HEADER
    DESTINATION ${INSTALL_INCLUDEDIR}/{{cookiecutter.project_name}}_utils
    COMPONENT dev
  )

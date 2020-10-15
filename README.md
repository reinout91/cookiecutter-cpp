cookiecutter-cpp
================

A test-driven C++ project template built on CMake and GoogleTest, that uses Armadillo as an example.

CMake is a fast and easy build tool.  
Use of GoogleTest test ensures robust code.  
Doxygen enables documentation.  
pmm is a package manager manager. You can configure your project to use Conan or VCPKG. This may become more important for cross platform development.

This template was made by combining:
Original Cookicutter project: https://github.com/hbristow/cookiecutter-cpp  
A lecture of Igor Bogoslavskyi: https://www.youtube.com/watch?v=q8xO2eJijy4&list=PLgnQpQtFTOGR50iIOtO36nK6aNPtVq98C&index=4  
Boilerplate pmm project: https://github.com/ariveron/boilerplate-pmm-vcpkg-cmake  
CMake Example: https://github.com/dev-cafe/cmake-cookbook/blob/master/chapter-10/recipe-01/cxx-example/CMakeLists.txt


Note: currently the Vcpkg version of Armadillo is not compiled using any wrappers. Therefore they must be explicitly disabled in the scripts that use them.
instead Vcpkg versions of OpenBLAS and LAPACK are linked explicitly.

Usage:
------

    $ pip install cookiecutter
    $ cookiecutter gh:reinout91/cookiecutter-cpp
    $ cd {project dir}/build
    $ cmake ..
    $ make
    $ ctest -vv
    $  ../bin/main
    $ make install
    
This template is tested on Windows (using msvc compiler) and Linux (using clang)
 

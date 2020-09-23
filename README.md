cookiecutter-cpp
================

Currently works only for Linux compilers, I'm currently changing the CMake scripts to make them compiler independent.

A test-driven C++ project template built on CMake and GoogleTest

CMake is a fast and easy build tool.  
GoogleTest test ensures robust code.  
Doxygen enables documentation.  
pmm is a package manager manager. You can configure your project to use Conan or VCPKG.

This template was made by combining:
Original Cookicutter project https://github.com/hbristow/cookiecutter-cpp  
A lecture of Igor Bogoslavskyi https://www.youtube.com/watch?v=q8xO2eJijy4&list=PLgnQpQtFTOGR50iIOtO36nK6aNPtVq98C&index=4  
Boilerplate pmm project https://github.com/ariveron/boilerplate-pmm-vcpkg-cmake



Usage:
------

    $ pip install cookiecutter
    $ cookiecutter gh:reinout91/cookiecutter-cpp
    $ cd {project dir}/build
    $ cmake ..
    $ make
    $ ctest -vv
    $  ../bin/main
    $ sudo make install
    

 

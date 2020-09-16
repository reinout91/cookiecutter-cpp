cookiecutter-cpp
================

A test-driven C++ project template built on CMake and GoogleTest

CMake is a fast and easy build tool.  
GoogleTest test ensures robust code.  
Doxygen enables documentation.  
pmm is a package manager manager. You can configure your project to use Conan or VCPKG.

This template was made by combining:
An existing Cookiecutter template with https://github.com/hbristow/cookiecutter-cpp with:  
A lecture of Igor Bogoslavskyi https://www.youtube.com/watch?v=q8xO2eJijy4&list=PLgnQpQtFTOGR50iIOtO36nK6aNPtVq98C&index=4 



Usage:
------

    $ pip install cookiecutter
    $ cookiecutter gh:reinout91/cookiecutter-cpp
    $ cd {project dir}/build
    $ cmake ..
    $ make
    $ ctest -vv
    $  ../bin/main
    

 

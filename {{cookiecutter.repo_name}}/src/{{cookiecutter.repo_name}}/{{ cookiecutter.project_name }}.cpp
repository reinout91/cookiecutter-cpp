#include <iostream>
#include <{{ cookiecutter.project_name }}Utils.h>
#include <fmt/core.h> //packagemanager downloaded library.
//#define ARMA_DONT_USE_WRAPPER
//#define ARMA_USE_LAPACK
//#define ARMA_USE_BLAS
#include <armadillo> //system wide installed package.

using namespace std;
using namespace arma;

int main()
{
  auto message = fmt::format("The answer is {}", sum(1,2));
  std::cout << message <<std::endl;
  mat v = randu<mat>(3,3);
  mat b = randu<mat>(3,3);
  std::cout << v*b << std::endl;
return EXIT_SUCCESS;
}


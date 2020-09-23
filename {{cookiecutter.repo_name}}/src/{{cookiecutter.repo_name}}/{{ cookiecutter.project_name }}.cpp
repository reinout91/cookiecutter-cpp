#include <iostream>
#include <{{ cookiecutter.project_name }}Utils.h>
#include <fmt/core.h> //packagemanager downloaded library.
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


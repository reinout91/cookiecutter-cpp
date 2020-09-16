#include <iostream>
#include <{{cookiecutter.repo_name}}_utils.h>
#include <fmt/core.h> //packagemanager downloaded library.
namespace std{

int main()
{
  auto message = fmt::format("The answer is {}", sum(1,2));
  std::cout << message <<std::endl;
return 0;
}
}

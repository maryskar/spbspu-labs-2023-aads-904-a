#include <iostream>
#include <fstream>
#include <string>
#include "calculator.h"
#include "stack.h"

void print(std::istream& streamInp, std::ostream& streamOut)
{
  Stack< long long > arr;
  std::string stringInp = "";

  do
  {
    std::getline(streamInp, stringInp);
    arr.push(calculateTheExpression(stringInp));
  }
  while (!streamInp.eof());

  while (!arr.isEmpty())
  {
    streamOut << arr.getTopData() << '\n';
    arr.popBack();
  }
}

int main(int argv, char** argc)
{
  try
  {
    if (argv == 2)
    {
      std::ifstream file(argc[1]);
      print(file, std::cout);
    }
    else
    {
      print(std::cin, std::cout);
    }
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << '\n';
    return 1;
  }

  return 0;
}

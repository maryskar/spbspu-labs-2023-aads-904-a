#include <iostream>
#include <fstream>
#include <string>
#include "calculator.h"
#include "stack.h"

void print(std::istream& streamInp, std::ostream& streamOut)
{
  Stack< long long > arr;
  std::string stringInp = "";

  while (streamInp)
  {
    std::getline(streamInp, stringInp);
    if (!streamInp)
    {
      break;
    }
    if (stringInp.find_first_not_of(" \n") == std::string::npos)
    {
      continue;
    }
    arr.push(calculateTheExpression(stringInp));
  }

  if (!arr.isEmpty())
  {
    streamOut << arr.getTopData();
    arr.popBack();
  }
  while (!arr.isEmpty())
  {
    streamOut << ' ' << arr.getTopData();
    arr.popBack();
  }
  streamOut << '\n';
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

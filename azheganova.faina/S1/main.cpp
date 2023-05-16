#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "convertfrominfixtopostfix.h"
#include "converttoinfix.h"
#include "calculate.h"
#include "queue.h"
#include "stack.h"

int main(int argc, char * argv[])
{
  if (argc > 2)
  {
    std::cout << "too much parameters";
    return 1;
  }
  std::fstream inputfile;
  if (argc == 2)
  {
    inputfile.open(argv[1]);
    if (!inputfile)
    {
      std::cerr << "error";
      return 1;
    }
  }
  std::istream& input = (argc == 2) ? inputfile : std::cin;
  std::string string;
  azheganova::Stack< long long > result;
  while (std::getline(input, string))
  {
    try
    {
      if (!input)
      {
        break;
      }
      if (string.empty())
      {
        continue;
      }
      azheganova::Queue< std::string > infixform = azheganova::convertToInfix(string);
      azheganova::Queue< std::string > postfixform;
      azheganova::Stack< std::string > stack;
      azheganova::convertFromInfixToPostfix(infixform, stack, postfixform);
      result.push(azheganova::calculatePostfix(postfixform));
    }
    catch (...)
    {
      std::cerr << "error";
      return 2;
    }
  }
  if (!result.isEmpty())
  {
    std::cout << result.get();
    result.pop();
    while (!result.isEmpty())
    {
      std::cout << " " << result.get();
      result.pop();
    }
  }
  std::cout << "\n";
  return 0;
}

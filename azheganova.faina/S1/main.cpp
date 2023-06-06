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
  namespace azh = azheganova;
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
  azh::Stack< long long > result;
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
      azh::Queue< std::string > infixform = azh::convertToInfix(string);
      azh::Queue< std::string > postfixform =azh::convertFromInfixToPostfix(infixform);
      result.push(azh::calculatePostfix(postfixform));
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

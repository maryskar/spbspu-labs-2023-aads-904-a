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
  std::string string;
  Stack < long long > result;
  if (argc > 2)
  {
    std::cout << "too much parameters";
    return 1;
  }
  if(argc == 2)
  {
    std::ifstream input(argv[1]);
    if (!input)
    {
      std::cerr << "error";
      return 1;
    }
    while (std::getline(input, string))
    {
      if (!input)
      {
        break;
      }
      if (string.empty())
      {
        continue;
      }
      Queue< std::string > infixform = convertToInfix(string);
      try
      {
        Queue< std::string > postfixform = convertFromInfixToPostfix(infixform);
        long long res = calculatePostfix(postfixform);
        result.push(res);
      }
      catch (const std::exception & e)
      {
        std::cerr << e.what() << "\n";
        return 2;
      }
    }
    if (!result.isEmpty())
    {
      std::cout << result.drop();
      result.pop();
      while (!result.isEmpty())
      {
        std::cout << " " << result.drop();
        result.pop();
      }
    }
  }
  else
  {
    while (std::cin)
    {
      std::getline(std::cin, string);
      if (!std::cin)
      {
        break;
      }
      if (string.empty())
      {
        continue;
      }
      Queue< std::string > infixform = convertToInfix(string);
      try
      {
        Queue< std::string > postfixform = convertFromInfixToPostfix(infixform);
        long long res = calculatePostfix(postfixform);
        result.push(res);
      }
      catch (const std::exception & e)
      {
        std::cerr << e.what() << "\n";
        return 2;
      }
    }
    if (!result.isEmpty())
    {
      std::cout << result.drop();
      result.pop();
      while (!result.isEmpty())
      {
        std::cout << " " << result.drop();
        result.pop();
      }
    }
  }
  std::cout << "\n";
  return 0;
}

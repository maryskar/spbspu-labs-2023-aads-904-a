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
  if (argc == 1)
  {
    std::cout << "no file name";
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
    std::string line;
    Stack < long long > results;
    while (std::getline(input, line))
    {
      if (!input)
      {
        break;
      }
      if (line.empty())
      {
        continue;
      }
      Queue< std::string > infix = convertToInfix(line);
      try
      {
        Queue< std::string > postfix = convertFromInfixToPostfix(infix);
        long long res = calculatePostfix(postfix);
        results.push(res);
      }
      catch (const std::exception & e)
      {
        std::cerr << e.what() << "\n";
        return 2;
      }
    }
    if (!results.isEmpty())
    {
      std::cout << results.drop();
      results.pop();
      while (!results.isEmpty())
      {
        std::cout << " " << results.drop();
        results.pop();
      }
    }
    input.close();
  }
}

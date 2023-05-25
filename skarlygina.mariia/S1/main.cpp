#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "queue.h"
#include "stack.h"
#include "postfix_prefix.h"
#include "count_postfix.h"

int main(int argc, char* argv[])
{
  if (argc > 1)
  {
    std::ifstream fin(argv[1]);
    if (!fin.is_open())
    {
      std::cerr << "Reading File could not be opened\n";
      return 1;
    }
  }

  std::istream* input = nullptr;
  if (argc > 1)
  {
    try
    {
      input = new std::ifstream(argv[1]);
    }
    catch (const std::bad_alloc& e)
    {
      e.what();
      delete input;
      return 1;
    }
  }
  else
  {
    input = &std::cin;
  }

  Stack< long long > stack;
  std::string line = "";
  while (std::getline(*input, line))
  {
    if (line.find_first_not_of("\n\t") == std::string::npos)
    {
      continue;
    }
    try
    {
      Queue< std::string > queue_inf = operation::makeInfix(line);
      Queue< std::string > queue_postfix = operation::makePostfix(queue_inf);
      long long res = countPostfix(queue_postfix);
      stack.push(res);
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << "\n";
      return 2;
    }
  }
  if (!stack.isEmpty())
  {
    std::cout << stack.get();
    stack.pop();
  }
  while (!stack.isEmpty())
  {
    std::cout << " " << stack.get();
    stack.pop();
  }
}

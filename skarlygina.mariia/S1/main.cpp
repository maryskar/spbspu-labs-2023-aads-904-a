#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "queue.h"
#include "stack.h"
#include "count_postfix.h"

int main(int argc, char* argv[])
{
  Queue< std::string > queue;
  Stack< long long > stack;
  std::ifstream infile;
  if (argc == 2)
  {
    infile.open(argv[1]);
    if (!infile.good())
    {
      std::cerr << "File could not be opened";
      return 1;
    }
  }
  if (argc > 2)
  {
    std::cerr << "Many argc";
    return 1;
  }
  std::istream& file = (argc == 1) ? std::cin : infile;
  try
  {
    while (!file.eof())
    {
      std::string math_string;
      std::getline(file, math_string);
      if (!math_string[0])
      {
        continue;
      }
      skarlygina::formatToPostfix(math_string, queue);
      skarlygina::countPostfix(queue, stack);
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "/n";
    return 2;
  }
  while (!stack.isEmpty())
  {
    std::cout << stack.top();
    stack.pop();
    if (!stack.isEmpty())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
  return 0;
}

#include <iostream>
#include <string>
#include <fstream>
#include <queue.h>
#include <stack.h>
#include "data-type.h"
#include "exp-work.h"

int main(int argc, char * argv[])
{
  Queue< calc_t > input;
  Queue< calc_t > output;
  std::string dirt, temp;
  calc_t data;
  if (argc == 2)
  {
    std::fstream file(argv[1]);
    if (!file.is_open())
    {
      std::cerr << "cannot open file\n";
      return 1;
    }
    std::getline(file, dirt);
  }
  else
  {
    std::getline(std::cin, dirt);
  }
  dirt += '\n';
  for (auto symbol : dirt)
  {
    if (symbol == ' ' || symbol == '\n')
    {
      try
      {
        data = std::stoll(temp);
      }
      catch (...)
      {
        data = temp.c_str()[0];
      }
      input.push(data);
      temp = "";
    }
    else
    {
      temp += symbol;
    }
  }
  try
  {
    long long result = 0;
    inf2Post(input, output);
    post2Result(output, result);
    std::cout << result << "\n";
  }
  catch (...)
  {
    std::cerr << "ERROR AAAAAAAAAAAA\n";
    return 1;
  }
  return 0;
}


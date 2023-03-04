#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <queue.h>
#include <stack.h>
#include "data-type.h"
#include "exp-work.h"

int main(int argc, char * argv[])
{
  std::ifstream file;
  if (argc == 2)
  {
    file.open(argv[1]);
    if (!file.is_open())
    {
      std::cerr << "cannot open file\n";
      return 1;
    }
    std::cin.rdbuf(file.rdbuf());
  }

  Queue< calc_t > input, output;
  Stack< long long > answers;
  std::string dirt;
  long long result = 0;
  try
  {
    while (std::cin)
    {
      std::getline(std::cin, dirt);
      if (!std::cin)
      {
        break;
      }
      if (!dirt.length())
      {
        continue;
      }
      dirt += "\n";
      str2Inf(dirt, input);
      inf2Post(input, output);
      post2Result(output, result);
      answers.push(result);
    }
  }
  catch (const std::exception & error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  if (!answers.isEmpty())
  {
    std::cout << answers.drop();
  }
  while (!answers.isEmpty())
  {
    std::cout << " " << answers.drop();
  }
  std::cout << "\n";
  return 0;
}


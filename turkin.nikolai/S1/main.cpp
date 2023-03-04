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
  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
      std::cerr << "cannot open file\n";
      return 1;
    }
    std::cin.rdbuf(file.rdbuf());
  }

  Queue< calc_t > input, output;
  std::string dirt;
  long long result = 0;
  try
  {
    while (std::cin)
    {
      std::getline(std::cin, dirt);
      if (!dirt.length())
      {
        continue;
      }
      dirt += "\n";
      str2Inf(dirt, input);
      inf2Post(input, output);
      post2Result(output, result);
      std::cout << result << " ";
    }
    std::cout << "\n";
  }
  catch (const std::exception & error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  return 0;
}


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
  }
  std::istream & in = (argc == 2) ? std::cin : file;
  Queue< calc_t > input, output;
  Stack< long long > answers;
  std::string dirt;
  try
  {
    while (in)
    {
      std::getline(in, dirt);
      if (!in)
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
      answers.push(post2Result(output));
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

  Stack< int > a;
  Stack< int > b;
  b = a;
  std::cout << a.drop() << "\n" << b.drop() << "\n";
  return 0;
}


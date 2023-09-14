#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "queue.h"
#include "stack.h"
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
}

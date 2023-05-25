#include <iostream>
#include <cstring>
#include <fstream>
#include "queue.h"
#include "stack.h"
#include "count.h"
#include "postfix_prefix.h"
#include "count_postfix.h"

int main(int argc, char* argv[])
{
  if (argc > 2)
  {
    std::cerr << "Error. The number of argc";
  }
  if (argc == 2)
  {
    std::ifstream fin(argv[1]);
    if (!fin.is_open())
    {
      std::cerr << "Reading File could not be opened\n";
      return 1;
    }
  }
}

#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <IOrealization.h>
#include "AVL.h"
#include "AVL_iterator.h"
#include "AVL_reverse_iter.h"
#include "TreeWithTraverses.h"
#include "const_AVL_iterator.h"
#include "const_AVL_reverse_iter.h"
#include "tree.h"

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    std::cerr << "Wrong number of arguments\n";
    return 1;
  }
  else
  {
    std::ifstream input;
    input.open(argv[2]);
    if (!input.is_open())
    {
      std::cerr << "Can't open file\n";
      return 1;
    }
    using dict = mashkin::AVL< int, std::string >;
    constexpr auto maxSize = std::numeric_limits< std::streamsize >::max();
    dict avl;
    while (!input.eof())
    {
      input >> avl;
      if (input.fail())
      {
        input.clear();
        input.ignore(maxSize, '\n');
      }
    }
    mashkin::AVL< std::string, void (*)(std::ostream&, dict&) > commands;
    mashkin::createTreeWithTraverses(commands);
    if (commands.contains(argv[1]))
    {
      commands[argv[1]](std::cout, avl);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
  return 0;
}

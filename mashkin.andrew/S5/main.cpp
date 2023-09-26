#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <AVL/AVL.h>
#include <IOstreamOverloads.h>
#include "TreeWithTraverses.h"

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
      try
      {
        input >> avl;
        if (input.fail())
        {
          input.clear();
          input.ignore(maxSize, '\n');
        }
      }
      catch (const std::exception& ex)
      {
        std::cerr << ex.what() << "\n";
        return 1;
      }
    }
    if (avl.empty())
    {
      std::cout << "<EMPTY>\n";
      return 0;
    }
    mashkin::AVL< std::string, void (*)(std::ostream&, dict&) > commands;
    commands = mashkin::createTreeWithTraverses();
    try
    {
      if (commands.contains(argv[1]))
      {
        commands[argv[1]](std::cout, avl);
        std::cout << "\n";
      }
      else
      {
        std::cerr << "<INVALID COMMAND>\n";
        return 1;
      }
    }
    catch (const std::exception& exception)
    {
      std::cerr << exception.what() << "\n";
      return 1;
    }
  }
  return 0;
}

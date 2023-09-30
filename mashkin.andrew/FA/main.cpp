#include <iostream>
#include <string>
#include "AVL/AVL.h"
#include "AVL/tree.h"
#include "createMapOfCommands.h"
#include "semanticTree.h"

int main()
{
  using MapOfExpressions = mashkin::AVL< std::string, mashkin::SemanticTree< std::string >* >;
  MapOfExpressions mapOfExpressions;
  mashkin::AVL< std::string, void (*)(std::istream&, MapOfExpressions&) > mapOfCommands;
  try
  {
    mapOfCommands = mashkin::createMapOfCommands();
    while (std::cin)
    {
      std::string command;
      std::cin >> command;
      if (mapOfCommands.contains(command))
      {
        mapOfCommands[command](std::cin, mapOfExpressions);
      }
      else
      {
        std::cerr << "<INVALID COMMAND>\n";
        return 1;
      }
    }
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what() << "\n";
    return 1;
  }
  return 0;
}

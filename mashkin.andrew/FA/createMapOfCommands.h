#ifndef MASHKIN_ANDREW_CREATEMAPOFCOMMANDS_H
#define MASHKIN_ANDREW_CREATEMAPOFCOMMANDS_H
#include <iostream>
#include <string>
#include "AVL/AVL.h"
#include "semanticTree.h"

namespace mashkin
{
  using MapOfExpressions = mashkin::AVL< std::string, mashkin::SemanticTree< std::string >* >;
  using MapOfCommands = AVL< std::string, void (*)(std::istream&, MapOfExpressions&) >;
  MapOfCommands createMapOfCommands();
}
#endif

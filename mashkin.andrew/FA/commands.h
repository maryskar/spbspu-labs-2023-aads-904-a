#ifndef MASHKIN_ANDREW_COMMANDS_H
#define MASHKIN_ANDREW_COMMANDS_H
#include <iostream>
#include <string>
#include "AVL/AVL.h"
#include "semanticTree.h"

namespace mashkin
{
  using MapOfExpressions = AVL< std::string, SemanticTree< std::string >* >;
  void addExpr(std::istream& inp, MapOfExpressions& map);
  void simplifyExpr(std::istream& inp, MapOfExpressions& map);
  void getParameters(std::istream& inp, MapOfExpressions& map);
  void setNewExpr(std::istream& inp, MapOfExpressions& map);
  void showExpr(std::istream& inp, MapOfExpressions& map);
}
#endif

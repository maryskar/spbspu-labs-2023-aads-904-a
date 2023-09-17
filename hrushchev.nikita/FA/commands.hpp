#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <avltree.hpp>
#include "queue.hpp"

namespace hrushchev
{
  void addToInfixDict(AVLTree< std::string, Queue< std::string > >& dict, const std::string& name, const std::string& expr);
  void addToPostfixDict
}

#endif


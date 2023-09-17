#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <avltree.hpp>
#include "queue.hpp"

namespace hrushchev
{
  void addToInfixDict(AVLTree< std::string, Queue< std::string > > dict, std::string name, std::string expr);
}

#endif


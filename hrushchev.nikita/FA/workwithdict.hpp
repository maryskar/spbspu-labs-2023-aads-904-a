#ifndef WORKWITHDICT_HPP
#define WORKWITHDICT_HPP

#include <string>
#include <avltree.hpp>
#include "queue.hpp"

namespace hrushchev
{
  class Command
  {
    public:
      Command();
    private:
      AVLTree< std::string, Queue< std::string > > dict_with_infix;
      AVLTree< std::string, Queue< std::string > > dict_with_postfix;
  };
}

#endif


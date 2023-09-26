#ifndef WORKWITHDICT_HPP
#define WORKWITHDICT_HPP

#include <iostream>
#include <avltree.hpp>
#include "traverses.hpp"

namespace hrushchev
{
  template< typename F >
  class TraversesDict
  {
    public:
      TraversesDict();
      void doTraverse(std::string name, const AVLTree< long long, std::string >& tree, F f);
    private:
      using com = void(*)(const AVLTree< long long, std::string >&, F);
      AVLTree< std::string, com > dict_;
  };
}

#endif

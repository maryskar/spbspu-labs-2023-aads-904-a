#ifndef WORKWITHDICT_HPP
#define WORKWITHDICT_HPP

#include <iostream>
#include "avltree.hpp"
#include "commands.hpp"

namespace hrushchev
{
  class Commands
  {
    public:
      Commands();
      void runCommand(std::istream& in, std::ostream& out, main_dict&);
    private:
      using com1 = void(*)(std::string, main_dict&, std::ostream&);
      using com2 = void(*)(std::string, std::string, std::string, main_dict&);

      AVLTree< std::string, com1 > dict1_;
      AVLTree< std::string, com2 > dict2_;
  };
}

#endif

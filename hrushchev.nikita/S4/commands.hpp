#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <avltree.hpp>

namespace hrushchev
{
  using dict_t = AVLTree< size_t, std::string >;

  void printDict(std::string name, AVLTree< std::string, dict_t >& dict_of_dict, std::ostream& out);
  void complementDict(std::string name, std::string first, std::string second, AVLTree< std::string, dict_t >& dict_of_dict);
  void intersectDict(std::string name, std::string first, std::string second, AVLTree< std::string, dict_t >& dict_of_dict);
  void unionDict(std::string name, std::string first, std::string second, AVLTree< std::string, dict_t >& dict_of_dict);
}

#endif

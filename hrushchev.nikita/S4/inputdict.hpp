#ifndef INPUTDICT_HPP
#define INPUTDICT_HPP

#include <istream>
#include <string>
#include <avltree.hpp>

namespace hrushchev
{
  using dict_t = AVLTree< size_t, std::string >;

  void inputDict(std::istream& input, AVLTree< std::string, dict_t >& dict_of_dict);
}

#endif

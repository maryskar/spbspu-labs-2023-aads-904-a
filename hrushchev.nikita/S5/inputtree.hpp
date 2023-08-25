#ifndef INPUTTREE_HPP
#define INPUTTREE_HPP
#include <istream>
#include <string>
#include <avltree.hpp>

namespace hrushchev
{
 void inputTree(std::istream& input, hrushchev::AVLTree< long long, std::string >& tree);
}

#endif

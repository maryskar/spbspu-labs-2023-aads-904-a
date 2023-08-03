#ifndef READDATAFORTREE_H
#define READDATAFORTREE_H
#include <iostream>
#include <string>
#include <RedBlackTree.h>

namespace tarasenko
{
  void readDataForTree(std::istream& in, RedBlackTree< std::pair< long long, std::string >, std::less<> >& tree);
}
#endif

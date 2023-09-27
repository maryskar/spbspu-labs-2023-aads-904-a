#include "readDataForTree.h"

void tarasenko::readDataForTree(std::istream& in,
   RedBlackTree< std::pair< long long, std::string >, std::less<> >& tree)
{
  long long key;
  std::string value;
  while (in >> key >> value)
  {
    if (in)
    {
      tree.insert({key, value});
    }
  }
}

#include "Traverses.h"
#include <iostream>
#include "IOrealization.h"

namespace mashkin
{
  void ascend(std::ostream& out, avl& tree)
  {
    QueueForTraverse res;
    tree.traverse_lnr(res);
    out << res.res_;
  }
}

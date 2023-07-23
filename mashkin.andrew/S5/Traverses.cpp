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

  void descend(std::ostream& out, avl& tree)
  {
    QueueForTraverse res;
    tree.traverse_rnl(res);
    out << res.res_;
  }

  void doBreadthTr(std::ostream& out, avl& tree)
  {
    StackForTraverse res;
    tree.traverse_breadth(res);
    out << res.res_;
  }
}

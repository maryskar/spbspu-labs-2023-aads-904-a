#include "Traverses.h"
#include <iostream>
#include <IOstreamOverloads.h>

namespace mashkin
{
  void ascend(std::ostream& out, avl& tree)
  {
    QueueForTraverse res;
    tree.traverse_lnr(res);
    out << res;
  }

  void descend(std::ostream& out, avl& tree)
  {
    QueueForTraverse res;
    tree.traverse_rnl(res);
    out << res;
  }

  void doBreadthTr(std::ostream& out, avl& tree)
  {
    StackForTraverse res;
    tree.traverse_breadth(res);
    out << res;
  }
}

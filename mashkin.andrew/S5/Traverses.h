#ifndef MASHKIN_ANDREW_TRAVERSES_H
#define MASHKIN_ANDREW_TRAVERSES_H
#include <iostream>
#include <AVL.h>
#include "structsForTraverse.h"

namespace mashkin
{
  using avl = AVL< int, std::string >;
  void ascend(std::ostream& out, avl& tree);
}
#endif

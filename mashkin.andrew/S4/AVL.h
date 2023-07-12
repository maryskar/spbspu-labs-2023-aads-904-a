#ifndef S4_AVL_H
#define S4_AVL_H
#include "tree.h"

namespace mashkin
{
  template< class T, class Comporator >
  class AVL
  {
  public:
    AVL();
    AVL(const AVL& lhs);
    AVL(AVL&& rhs);
    ~AVL();

  private:
    Tree< T, Comporator > root_;
    Comporator comp_;
  };
}
#endif

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


    void clear();
  private:
    Tree< T, Comporator > root_;
    Comporator comp_;
  };

  template< class T, class Comp >
  AVL< T, Comp >::AVL():
    root_(static_cast< Tree< T, Comp >* >(::operator new(sizeof(Tree< T, Comp >)))),
    comp_()
  {
    root_.left = nullptr;
    root_.right = nullptr;
  }
}
#endif

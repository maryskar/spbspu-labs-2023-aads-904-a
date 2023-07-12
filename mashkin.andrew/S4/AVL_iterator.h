#ifndef S4_AVL_ITERATOR_H
#define S4_AVL_ITERATOR_H
#include <functional>
#include <iterator>
#include "tree.h"

namespace mashkin
{
  template< class T, class Comporator = std::less< T > >
  class AVL_iterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    AVL_iterator();
    ~AVL_iterator() = default;
    explicit AVL_iterator(const AVL_iterator< T >&) = default;
    explicit AVL_iterator(Tree< T >* rhs);

    AVL_iterator< T >& operator=(const AVL_iterator< T >&) = default;
    AVL_iterator< T >& operator++();
    AVL_iterator< T > operator++(int);
    AVL_iterator< T >& operator--();
    AVL_iterator< T > operator--(int);

    T& operator*();
    T* operator->();

    bool operator!=(const AVL_iterator< T >& rhs) const;
    bool operator==(const AVL_iterator< T >& rhs) const;

  private:
    Tree< T >* node_;
    Comporator comp_;
  };

  template< class T, class Comp >
  AVL_iterator< T, Comp >::AVL_iterator():
    node_(nullptr),
    comp_()
  {
  }

  template< class T, class Comp >
  AVL_iterator< T, Comp >::AVL_iterator(Tree< T >* rhs):
    node_(rhs),
    comp_()
  {
  }
}
#endif

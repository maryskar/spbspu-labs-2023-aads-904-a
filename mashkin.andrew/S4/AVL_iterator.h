#ifndef S4_AVL_ITERATOR_H
#define S4_AVL_ITERATOR_H
#include <iterator>
#include "tree.h"

namespace mashkin
{
  template< class T >
  class AVL_iterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    AVL_iterator();
    ~AVL_iterator() = default;
    AVL_iterator(const AVL_iterator< T >&) = default;
    AVL_iterator(Tree< T >* rhs);

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
    Tree< T >* node;
  };
}
#endif

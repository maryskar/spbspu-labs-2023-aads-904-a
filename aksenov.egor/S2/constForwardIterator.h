#ifndef CONSTFORWARDITERATOR_H
#define CONSTFORWARDITERATOR_H
#include <cassert>
#include "List.h"
namespace aksenov
{
  template< typename T >
  class ConstForwardIterator
  {
  public:
    ConstForwardIterator();
    ~ConstForwardIterator() = default;
    ConstForwardIterator(listT< T > *node);
    ConstForwardIterator(const ConstForwardIterator< T > &) = default;
    ConstForwardIterator< T > &operator=(const ConstForwardIterator< T > &rhs) = default;

    ConstForwardIterator< T > &operator++();
    ConstForwardIterator< T > &operator++(int) const;

    const T &operator*() const;
    const T *operator->() const;

    bool operator!=(const ConstForwardIterator< T > &rhs) const;
    bool operator==(const ConstForwardIterator< T > &rhs) const;

  private:
    listT< T > *node_;
  };

}
#endif

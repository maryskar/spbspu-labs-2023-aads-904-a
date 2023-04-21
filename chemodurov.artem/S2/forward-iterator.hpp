#ifndef S2_FORWARD_ITERATOR_HPP
#define S2_FORWARD_ITERATOR_HPP
#include <list.hpp>

namespace chemodurov
{
  template< typename T >
  class ForwardIterator
  {
   public:
    ForwardIterator(): node_(nullptr) {};
    ~ForwardIterator() = default;
    ForwardIterator(const ForwardIterator< T > &) = default;
    ForwardIterator< T > & operator=(const ForwardIterator< T > &) = default;
    ForwardIterator< T > & operator++();
    ForwardIterator< T > operator++(int);
    T & operator*();
    const T & operator*() const;
    T * operator->();
    const T * operator->() const;
    bool operator==(const ForwardIterator< T > &) const;
    bool operator!=(const ForwardIterator< T > &) const;
   private:
    List< T > * node_;
  };
}

#endif

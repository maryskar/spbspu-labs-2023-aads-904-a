#ifndef S2_FORWARD_ITERATOR_HPP
#define S2_FORWARD_ITERATOR_HPP
#include <cassert>
#include <list.hpp>

namespace chemodurov
{
  template< typename T >
  class ForwardIterator
  {
   public:
    ForwardIterator(): node_(nullptr) {};
    ~ForwardIterator() = default;
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
    void assertNotNullptr();
    void assertNotNullptr() const;
  };

  template< typename T >
  void ForwardIterator< T >::assertNotNullptr() const
  {
    assert(node_ != nullptr);
  }

  template< typename T >
  void ForwardIterator< T >::assertNotNullptr()
  {
    (static_cast< const ForwardIterator< T > >(*this)).assertNotNullptr();
  }

  template< typename T >
  ForwardIterator< T > & ForwardIterator< T >::operator++()
  {
    assertNotNullptr();
    node_ = node_->next;
    return node_;
  }

  template< typename T >
  ForwardIterator< T > ForwardIterator< T >::operator++(int)
  {
    assertNotNullptr();
    ForwardIterator< T > temp(*this);
    ++(*this);
    return temp;
  }

  template< typename T >
  const T & ForwardIterator< T >::operator*() const
  {
    assertNotNullptr();
    return node_->data;
  }

  template< typename T >
  T & ForwardIterator< T >::operator*()
  {
    return const_cast< T & >(*(static_cast< const ForwardIterator< T > >(*this)));
  }

  template< typename T >
  const T * ForwardIterator< T >::operator->() const
  {
    assertNotNullptr();
    return std::addressof(node_->data);
  }

  template< typename T >
  T * ForwardIterator< T >::operator->()
  {
    return const_cast< T * >((static_cast< const ForwardIterator< T > >(*this)).node_->data);
  }

  template< typename T >
  bool ForwardIterator< T >::operator==(const ForwardIterator< T > & rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename T >
  bool ForwardIterator< T >::operator!=(const ForwardIterator< T > & rhs) const
  {
    return !(*this == rhs);
  }
}

#endif

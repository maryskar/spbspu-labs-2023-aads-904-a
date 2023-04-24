#ifndef S2_CONST_FORWARD_ITERATOR_HPP
#define S2_CONST_FORWARD_ITERATOR_HPP
#include <cassert>
#include <list.hpp>
#include "forward-iterator.hpp"

namespace chemodurov
{
  template< typename T >
  class ConstForwardIterator
  {
   public:
    using this_t = ConstForwardIterator< T >;
    ConstForwardIterator(): node_(nullptr) {};
    explicit ConstForwardIterator(ForwardIterator< T > rhs);
    ~ConstForwardIterator() = default;
    this_t & operator=(const this_t & rhs) = default;
    this_t & operator++();
    this_t operator++(int);
    T & operator*();
    const T & operator*() const;
    T * operator->();
    const T * operator->() const;
    bool operator==(const this_t & rhs) const;
    bool operator!=(const this_t & rhs) const;
   private:
    const detail::List< T > * node_;
    explicit ConstForwardIterator(const detail::List< T > * list): node_(list) {};
    void assertNotNullptr();
    void assertNotNullptr() const;
  };

  template< typename T >
  void ConstForwardIterator< T >::assertNotNullptr() const
  {
    assert(node_ != nullptr);
  }

  template< typename T >
  void ConstForwardIterator< T >::assertNotNullptr()
  {
    (static_cast< const this_t >(*this)).assertNotNullptr();
  }

  template< typename T >
  ConstForwardIterator< T > & ConstForwardIterator< T >::operator++()
  {
    assertNotNullptr();
    node_ = node_->next;
    return node_;
  }

  template< typename T >
  ConstForwardIterator< T > ConstForwardIterator< T >::operator++(int)
  {
    this_t temp(*this);
    ++(*this);
    return temp;
  }

  template< typename T >
  const T & ConstForwardIterator< T >::operator*() const
  {
    return node_->data;
  }

  template< typename T >
  T & ConstForwardIterator< T >::operator*()
  {
    return const_cast< T & >((static_cast< const this_t >(*this)).operator*());
  }

  template< typename T >
  const T * ConstForwardIterator< T >::operator->() const
  {
    return std::addressof(node_->data);
  }

  template< typename T >
  T * ConstForwardIterator< T >::operator->()
  {
    return const_cast< T * >((static_cast< const this_t >(*this)).operator->());
  }

  template< typename T >
  bool ConstForwardIterator< T >::operator==(const ConstForwardIterator::this_t & rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename T >
  bool ConstForwardIterator< T >::operator!=(const ConstForwardIterator::this_t & rhs) const
  {
    return !(*this == rhs);
  }

  template< typename T >
  ConstForwardIterator< T >::ConstForwardIterator(ForwardIterator< T > rhs):
   node_(static_cast< const detail::List< T > * >(rhs.node_))
  {}
}

#endif

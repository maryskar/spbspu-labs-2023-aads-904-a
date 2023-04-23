#ifndef S2_FORWARD_ITERATOR_HPP
#define S2_FORWARD_ITERATOR_HPP
#include <cassert>
#include <list.hpp>

namespace chemodurov
{
  template< typename T >
  class ConstForwardIterator;

  template< typename T >
  class ForwardIterator
  {
    friend class ConstForwardIterator< T >;
   public:
    using this_t = ForwardIterator< T >;
    ForwardIterator(): node_(nullptr) {};
    ~ForwardIterator() = default;
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
    detail::List< T > * node_;
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
    return const_cast< T & >((static_cast< const ForwardIterator< T > >(*this)).operator*());
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
    return const_cast< T * >((static_cast< const ForwardIterator< T > >(*this)).operator->());
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

#ifndef S2_FORWARD_ITERATOR_HPP
#define S2_FORWARD_ITERATOR_HPP
#include <cassert>
#include <iterator>
#include <list.hpp>

namespace chemodurov
{
  template< typename T >
  class ConstForwardIterator;

  template< typename T >
  class ForwardList;

  template< typename T >
  class ForwardIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    friend class ConstForwardIterator< T >;
    friend class ForwardList< T >;
   public:
    using this_t = ForwardIterator< T >;
    ForwardIterator();
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
    explicit ForwardIterator(detail::List< T > * list);
  };

  template< typename T >
  ForwardIterator< T > & ForwardIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  ForwardIterator< T > ForwardIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    ForwardIterator< T > temp(*this);
    ++(*this);
    return temp;
  }

  template< typename T >
  const T & ForwardIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
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
    assert(node_ != nullptr);
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

  template< typename T >
  ForwardIterator< T >::ForwardIterator():
   node_(nullptr)
  {}

  template< typename T >
  ForwardIterator< T >::ForwardIterator(detail::List< T > * list):
   node_(list)
  {}
}

#endif

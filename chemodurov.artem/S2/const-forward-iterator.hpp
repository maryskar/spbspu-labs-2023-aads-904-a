#ifndef S2_CONST_FORWARD_ITERATOR_HPP
#define S2_CONST_FORWARD_ITERATOR_HPP
#include <cassert>
#include <list.hpp>

namespace chemodurov
{
  template< typename T >
  class ForwardList;

  template< typename T >
  class ForwardIterator;

  template< typename T >
  class ConstForwardIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    friend class ForwardList< T >;
   public:
    using this_t = ConstForwardIterator< T >;
    ConstForwardIterator();
    ConstForwardIterator(ForwardIterator< T > rhs);
    ~ConstForwardIterator() = default;
    this_t & operator=(const this_t & rhs) = default;
    this_t & operator++();
    this_t operator++(int);
    const T & operator*() const;
    const T * operator->() const;
    bool operator==(const this_t & rhs) const;
    bool operator!=(const this_t & rhs) const;
   private:
    detail::List< T > * node_;
    explicit ConstForwardIterator(detail::List< T > * list);
  };

  template< typename T >
  ConstForwardIterator< T > & ConstForwardIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  ConstForwardIterator< T > ConstForwardIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t temp(*this);
    ++(*this);
    return temp;
  }

  template< typename T >
  const T & ConstForwardIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  const T * ConstForwardIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
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
   node_(rhs.node_)
  {}

  template< typename T >
  ConstForwardIterator< T >::ConstForwardIterator():
   node_(nullptr)
  {}

  template< typename T >
  ConstForwardIterator< T >::ConstForwardIterator(detail::List< T > * list):
   node_(list)
  {}
}

#endif

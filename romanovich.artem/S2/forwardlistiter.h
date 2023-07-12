#ifndef FORWARDLISTITER_H
#define FORWARDLISTITER_H
#include <iterator>
#include <cstddef>
#include <memory>
#include "common/listnode.h"
namespace romanovich
{
  template< typename T >
  class ForwardList;
  template< typename T >
  class ConstForwardListIterator;
  template< typename T >
  class ForwardListIterator
  {
  public:
    friend class ForwardList< T >;
    friend class ConstForwardListIterator< T >;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    ForwardListIterator();
    explicit ForwardListIterator(const ConstForwardListIterator< T > &other);
    ~ForwardListIterator() = default;
    T &operator*();
    const T &operator*() const;
    T *operator->();
    const T *operator->() const;
    bool operator!=(const ForwardListIterator< T > &other) const;
    bool operator==(const ForwardListIterator< T > &other) const;
    ForwardListIterator< T > &operator=(const ForwardListIterator< T > &other) = default;
    ForwardListIterator< T > &operator=(const ConstForwardListIterator< T > &other);
    ForwardListIterator< T > &operator++();
    ForwardListIterator< T > operator++(int);
    ForwardListIterator< T > begin();
    ForwardListIterator< T > end();
  private:
    details::ListNode< T > *head_;
    explicit ForwardListIterator(details::ListNode< T > *otherHead);
  };
  template< typename T >
  ForwardListIterator< T > &ForwardListIterator< T >::operator=(const ConstForwardListIterator< T > &other)
  {
    head_ = other.head_;
    return *this;
  }
  template< typename T >
  ForwardListIterator< T >::ForwardListIterator(const ConstForwardListIterator< T > &other):
    head_(other.head_)
  {
  }
  template< typename T >
  ForwardListIterator< T >::ForwardListIterator(details::ListNode< T > *otherHead):
    head_(otherHead)
  {
  }
  template< typename T >
  ForwardListIterator< T > ForwardListIterator< T >::end()
  {
    return ForwardListIterator< T >(nullptr);
  }
  template< typename T >
  ForwardListIterator< T > ForwardListIterator< T >::begin()
  {
    return ForwardListIterator< T >(head_);
  }
  template< typename T >
  bool ForwardListIterator< T >::operator==(const ForwardListIterator< T > &other) const
  {
    return head_ == other.head_;
  }
  template< typename T >
  bool ForwardListIterator< T >::operator!=(const ForwardListIterator< T > &other) const
  {
    return head_ != other.head_;
  }
  template< typename T >
  T *ForwardListIterator< T >::operator->()
  {
    return std::addressof(head_->data_);
  }
  template< typename T >
  const T *ForwardListIterator< T >::operator->() const
  {
    return const_cast< T & >(static_cast< const ForwardListIterator< T >>(*this).operator*());
  }
  template< typename T >
  const T &ForwardListIterator< T >::operator*() const
  {
    return head_->data_;
  }
  template< typename T >
  T &ForwardListIterator< T >::operator*()
  {
    return const_cast<T &>(head_->data_);
  }
  template< typename T >
  ForwardListIterator< T > &ForwardListIterator< T >::operator++()
  {
    head_ = head_->next_;
    return *this;
  }
  template< typename T >
  ForwardListIterator< T > ForwardListIterator< T >::operator++(int)
  {
    ForwardListIterator< T > oldIter(*this);
    ++(*this);
    return oldIter;
  }
  template< typename T >
  ForwardListIterator< T >::ForwardListIterator():
    head_(nullptr)
  {
  }
}
#endif

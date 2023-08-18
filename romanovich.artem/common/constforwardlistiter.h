#ifndef CONSTFORWARDLISTITER_H
#define CONSTFORWARDLISTITER_H
#include "listnode.h"
namespace romanovich
{
  template< typename T >
  class ForwardList;
  template< typename T >
  class ForwardListIterator;
  template< typename T >
  class ConstForwardListIterator
  {
  public:
    friend class ForwardList< T >;
    friend class ForwardListIterator< T >;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    ConstForwardListIterator();
    explicit ConstForwardListIterator(const ForwardListIterator< T > &other);
    ~ConstForwardListIterator() = default;
    T &operator*();
    const T &operator*() const;
    T *operator->();
    const T *operator->() const;
    bool operator!=(const ConstForwardListIterator< T > &other) const;
    bool operator==(const ConstForwardListIterator< T > &other) const;
    ConstForwardListIterator< T > &operator=(const ConstForwardListIterator< T > &other) = default;
    ConstForwardListIterator< T > &operator=(const ForwardListIterator< T > &other);
    ConstForwardListIterator< T > &operator++();
    ConstForwardListIterator< T > operator++(int);
    ConstForwardListIterator< T > begin();
    ConstForwardListIterator< T > end();
  private:
    details::ListNode< T > *head_;
    explicit ConstForwardListIterator(details::ListNode< T > *otherHead);
  };
  template< typename T >
  ConstForwardListIterator< T > ConstForwardListIterator< T >::begin()
  {
    return ConstForwardListIterator< T >(head_);
  }
  template< typename T >
  ConstForwardListIterator< T > ConstForwardListIterator< T >::end()
  {
    return ConstForwardListIterator< T >(nullptr);
  }
  template< typename T >
  ConstForwardListIterator< T > &ConstForwardListIterator< T >::operator=(const ForwardListIterator< T > &other)
  {
    head_ = other.head_;
    return *this;
  }
  template< typename T >
  ConstForwardListIterator< T >::ConstForwardListIterator(const ForwardListIterator< T > &other):
    head_(other.head_)
  {
  }
  template< typename T >
  ConstForwardListIterator< T >::ConstForwardListIterator(details::ListNode< T > *otherHead):
    head_(otherHead)
  {
  }
  template< typename T >
  bool ConstForwardListIterator< T >::operator==(const ConstForwardListIterator< T > &other) const
  {
    return head_ == other.head_;
  }
  template< typename T >
  bool ConstForwardListIterator< T >::operator!=(const ConstForwardListIterator< T > &other) const
  {
    return head_ != other.head_;
  }
  template< typename T >
  const T *ConstForwardListIterator< T >::operator->() const
  {
    return std::addressof(head_->data_);
  }
  template< typename T >
  T *ConstForwardListIterator< T >::operator->()
  {
    return const_cast< T * >(std::addressof(head_->data_));
  }
  template< typename T >
  const T &ConstForwardListIterator< T >::operator*() const
  {
    return head_->data_;
  }
  template< typename T >
  T &ConstForwardListIterator< T >::operator*()
  {
    return const_cast<T &>(head_->data_);
  }
  template< typename T >
  ConstForwardListIterator< T > &ConstForwardListIterator< T >::operator++()
  {
    head_ = head_->next_;
    return *this;
  }
  template< typename T >
  ConstForwardListIterator< T > ConstForwardListIterator< T >::operator++(int)
  {
    ConstForwardListIterator< T > oldIter(*this);
    ++(*this);
    return oldIter;
  }
  template< typename T >
  ConstForwardListIterator< T >::ConstForwardListIterator():
    head_(nullptr)
  {
  }
}
#endif

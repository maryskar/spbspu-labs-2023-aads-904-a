#ifndef CONSTFORWARDLISTITER_H
#define CONSTFORWARDLISTITER_H
#include "common/listnode.h"
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
  using iterator_category = std::forward_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;
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
  explicit ConstForwardListIterator(details::ListNode< T > *otherHead);
  explicit ConstForwardListIterator(const ForwardListIterator< T > &other);
  ~ConstForwardListIterator() = default;
  ConstForwardListIterator< T > begin();
  ConstForwardListIterator< T > end();
private:
  ConstForwardListIterator();
  details::ListNode< T > *head_;
  void checkForNullNode();
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
  checkForNullNode();
  return std::addressof(head_->data_);
}
template< typename T >
T *ConstForwardListIterator< T >::operator->()
{
  checkForNullNode();
  return const_cast< T * >(std::addressof(head_->data_));
}
template< typename T >
void ConstForwardListIterator< T >::checkForNullNode()
{
  if (!head_)
  {
    throw std::runtime_error("head is null");
  }
}
template< typename T >
const T &ConstForwardListIterator< T >::operator*() const
{
  checkForNullNode();
  return head_->data_;
}
template< typename T >
T &ConstForwardListIterator< T >::operator*()
{
  checkForNullNode();
  return const_cast<T &>(head_->data_);
}
template< typename T >
ConstForwardListIterator< T > &ConstForwardListIterator< T >::operator++()
{
  checkForNullNode();
  head_ = head_->next_;
  return *this;
}
template< typename T >
ConstForwardListIterator< T > ConstForwardListIterator< T >::operator++(int)
{
  checkForNullNode();
  ConstForwardListIterator< T > oldIter(*this);
  ++(*this);
  return oldIter;
}
template< typename T >
ConstForwardListIterator< T >::ConstForwardListIterator():
  head_(nullptr)
{
}
#endif

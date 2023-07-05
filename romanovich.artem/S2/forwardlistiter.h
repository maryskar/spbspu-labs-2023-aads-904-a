#ifndef FORWARDLISTITER_H
#define FORWARDLISTITER_H
#include "common/listnode.h"
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
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;
  T &operator*();
  const T &operator*() const;
  T *operator->();
  const T *operator->() const;
  bool operator!=(const ForwardListIterator< T > &rhs) const;
  bool operator==(const ForwardListIterator< T > &rhs) const;
  ForwardListIterator< T > &operator=(const ForwardListIterator< T > &rhs) = default;
  ForwardListIterator< T > &operator++();
  ForwardListIterator< T > operator++(int);
  ForwardListIterator(details::ListNode< T > *head);
  ~ForwardListIterator() = default;
  ForwardListIterator();
  ForwardListIterator< T > begin();
  ForwardListIterator< T > end();
private:
  details::ListNode< T > *head_;
  void checkForNullNode();
};
template< typename T >
ForwardListIterator< T >::ForwardListIterator(details::ListNode< T > *head):
  head_(head)
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
void ForwardListIterator< T >::checkForNullNode()
{
  if (!head_)
  {
    throw std::runtime_error("head_ is null in operator++");
  }
}
template< typename T >
bool ForwardListIterator< T >::operator==(const ForwardListIterator< T > &rhs) const
{
  return head_ = rhs.head_;
}
template< typename T >
bool ForwardListIterator< T >::operator!=(const ForwardListIterator< T > &rhs) const
{
  return !(head_ == rhs.head_);
}
template< typename T >
T *ForwardListIterator< T >::operator->()
{
  checkForNullNode();
  return std::addressof(head_->data_);
}
template< typename T >
const T *ForwardListIterator< T >::operator->() const
{
  checkForNullNode();
  return const_cast< T & >(static_cast< const ForwardListIterator< T >>(*this).operator*());
}
template< typename T >
const T &ForwardListIterator< T >::operator*() const
{
  checkForNullNode();
  return head_->data;
}
template< typename T >
T &ForwardListIterator< T >::operator*()
{
  checkForNullNode();
  return const_cast<T &>(head_->data_);
}
template< typename T >
ForwardListIterator< T > &ForwardListIterator< T >::operator++()
{
  checkForNullNode();
  head_ = head_->next_;
  return *this;
}
template< typename T >
ForwardListIterator< T > ForwardListIterator< T >::operator++(int)
{
  checkForNullNode();
  ForwardListIterator< T > oldIter(*this);
  ++(*this);
  return oldIter;
}
template< typename T >
ForwardListIterator< T >::ForwardListIterator():
  head_(nullptr)
{
}
#endif

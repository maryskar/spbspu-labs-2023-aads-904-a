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
  bool operator!=(const ConstForwardListIterator< T > &rhs) const;
  bool operator==(const ConstForwardListIterator< T > &rhs) const;
  ConstForwardListIterator< T > &operator=(const ConstForwardListIterator< T > &rhs) = default;
  ConstForwardListIterator< T > &operator++();
  ConstForwardListIterator< T > operator++(int);
  ConstForwardListIterator(const ConstForwardListIterator< T > &rhs) = default;
private:
  ConstForwardListIterator();
  ~ConstForwardListIterator() = default;
  details::ListNode< T > *node_;
  void checkForNullNode();
};
template< typename T >
bool ConstForwardListIterator< T >::operator==(const ConstForwardListIterator< T > &rhs) const
{
  return node_ == rhs.node_;
}
template< typename T >
bool ConstForwardListIterator< T >::operator!=(const ConstForwardListIterator< T > &rhs) const
{
  return !(node_ == rhs.node_);
}
template< typename T >
const T *ConstForwardListIterator< T >::operator->() const
{
  checkForNullNode();
  return std::addressof(node_->data_);
}
template< typename T >
T *ConstForwardListIterator< T >::operator->()
{
  checkForNullNode();
  return const_cast<T *>(std::addressof(node_->data_));
}
template< typename T >
void ConstForwardListIterator< T >::checkForNullNode()
{
  if (!node_)
  {
    throw std::runtime_error("begin_ is null in operator++");
  }
}
template< typename T >
const T &ConstForwardListIterator< T >::operator*() const
{
  checkForNullNode();
  return node_->data;
}
template< typename T >
T &ConstForwardListIterator< T >::operator*()
{
  checkForNullNode();
  return const_cast<T &>(node_->data);
}
template< typename T >
ConstForwardListIterator< T > &ConstForwardListIterator< T >::operator++()
{
  checkForNullNode();
  node_ = node_->next_;
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
  node_(nullptr)
{
}
#endif

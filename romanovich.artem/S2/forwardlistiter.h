#ifndef FORWARDLISTITER_H
#define FORWARDLISTITER_H
template< typename T >
class ForwardListIterator
{
public:
  T &operator*();
  const T &operator*() const;
  T *operator->();
  const T *operator->() const;
  bool operator!=(const ForwardListIterator< T > &rhs) const;
  bool operator==(const ForwardListIterator< T > &rhs) const;
  ForwardListIterator< T > &operator=(const ForwardListIterator< T > &rhs) = default;
  ForwardListIterator< T > &operator++();
  ForwardListIterator< T > operator++(int);
  ForwardListIterator(const ForwardListIterator< T > &rhs) = default;
  ~ForwardListIterator() = default;
  ForwardListIterator();
private:
  details::ListNode< T > *node_;
  void checkForNullNode();
};
template< typename T >
void ForwardListIterator< T >::checkForNullNode()
{
  if (!node_)
  {
    throw std::runtime_error("node_ id null in operator++");
  }
}
template< typename T >
bool ForwardListIterator< T >::operator==(const ForwardListIterator< T > &rhs) const
{
  return node_ = rhs.node_;
}
template< typename T >
bool ForwardListIterator< T >::operator!=(const ForwardListIterator< T > &rhs) const
{
  return !(node_ == rhs.node_);
}
template< typename T >
const T *ForwardListIterator< T >::operator->() const
{
  checkForNullNode();
  return std::addressof(node_->data_);
}
template< typename T >
T *ForwardListIterator< T >::operator->()
{
  checkForNullNode();
  return const_cast< T & >(static_cast< const ForwardListIterator< T >>(*this).operator*());
}
template< typename T >
const T &ForwardListIterator< T >::operator*() const
{
  checkForNullNode();
  return node_->data;
}
template< typename T >
T &ForwardListIterator< T >::operator*()
{
  checkForNullNode();
  return const_cast<T &>(node_->data);
}
template< typename T >
ForwardListIterator< T > &ForwardListIterator< T >::operator++()
{
  checkForNullNode();
  node_ = node_->next_;
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
  node_(nullptr)
{
}
#endif

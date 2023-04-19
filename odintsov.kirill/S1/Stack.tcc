#include <stdexcept>

template< typename T >
odintsov::Stack< T >::Stack():
  tail_(nullptr)
{}

template< typename T >
odintsov::Stack< T >::Stack(const Stack< T >& s):
  tail_(nullptr)
{
  tail_ = detail::duplicateNodes(s.tail_).first;
}

template< typename T >
odintsov::Stack< T >::Stack(Stack< T >&& s):
  tail_(s.tail_)
{
  s.tail_ = nullptr;
}

template< typename T >
odintsov::Stack< T >::~Stack()
{
  detail::deleteNodes(tail_);
}

template< typename T >
odintsov::Stack< T >& odintsov::Stack< T >::operator=(const Stack< T >& s)
{
  if (this == &s) {
    return *this;
  }
  detail::Node< T >* oldTail = tail_;
  tail_ = detail::duplicateNodes(s.tail_).first;
  detail::deleteNodes(oldTail);
  return *this;
}

template< typename T >
odintsov::Stack< T >& odintsov::Stack< T >::operator=(Stack< T >&& s)
{
  detail::deleteNodes(tail_);
  tail_ = s.tail_;
  s.tail_ = nullptr;
  return *this;
}

template< typename T >
T& odintsov::Stack< T >::tail()
{
  return const_cast< T& >(const_cast< const Stack< T >* >(this)->tail());
}

template< typename T >
const T& odintsov::Stack< T >::tail() const
{
  if (empty()) {
    throw std::runtime_error("Attempt to get tail of empty stack");
  }
  return tail_->data;
}

template< typename T >
detail::ConstNodeIter< T > odintsov::Stack< T >::cbegin() const
{
  detail::ConstNodeIter< T > iter;
  iter.nodePtr = tail_;
  return iter;
}

template< typename T >
detail::ConstNodeIter< T > odintsov::Stack< T >::cend() const
{
  return detail::ConstNodeIter< T >();
}

template< typename T >
void odintsov::Stack< T >::push(const T& data)
{
  push(new detail::Node< T >{data, tail_});
}

template< typename T >
void odintsov::Stack< T >::push(T&& data)
{
  push(new detail::Node< T >{data, tail_});
}

template< typename T >
void odintsov::Stack< T >::push(detail::Node< T >* n)
{
  tail_ = n;
}

template< typename T >
void odintsov::Stack< T >::pop()
{
  if (empty()) {
    throw std::runtime_error("Attempt to pop empty stack");
  }
  detail::Node< T >* oldTail = tail_;
  tail_ = tail_->next;
  delete oldTail;
}

template< typename T >
bool odintsov::Stack< T >::empty() const
{
  return !tail_;
}

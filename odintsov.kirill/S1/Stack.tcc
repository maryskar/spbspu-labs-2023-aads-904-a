#include <stdexcept>
#include <tuple>

template< typename T >
odintsov::Stack< T >::Stack():
  head_(nullptr),
  tail_(nullptr)
{}

template< typename T >
odintsov::Stack< T >::Stack(const Stack< T >& s):
  head_(nullptr),
  tail_(nullptr)
{
  std::tie(tail_, head_) = duplicateNodes(s.tail_);
}

template< typename T >
odintsov::Stack< T >::Stack(Stack< T >&& s):
  head_(s.head_),
  tail_(s.tail_)
{
  s.head_ = nullptr;
  s.tail_ = nullptr;
}

template< typename T >
odintsov::Stack< T >::~Stack()
{
  deleteNodes(tail_);
}

template< typename T >
odintsov::Stack< T >& odintsov::Stack< T >::operator=(const Stack< T >& s)
{
  if (this == &s) {
    return *this;
  }
  Node< T >* oldTail = tail_;
  std::tie(tail_, head_) = duplicateNodes(s.tail_);
  deleteNodes(oldTail);
  return *this;
}

template< typename T >
odintsov::Stack< T >& odintsov::Stack< T >::operator=(Stack< T >&& s)
{
  deleteNodes(tail_);
  head_ = s.head_;
  tail_ = s.tail_;
  s.head_ = nullptr;
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
void odintsov::Stack< T >::push(const T& data)
{
  push(new Node< T >{data, tail_});
}

template< typename T >
void odintsov::Stack< T >::push(T&& data)
{
  push(new Node< T >{data, tail_});
}

template< typename T >
void odintsov::Stack< T >::push(Node< T >* n)
{
  if (empty()) {
    head_ = n;
  }
  tail_ = n;
}

template< typename T >
void odintsov::Stack< T >::pop()
{
  if (empty()) {
    throw std::runtime_error("Attempt to pop empty stack");
  }
  Node< T >* oldTail = tail_;
  tail_ = tail_->next;
  if (!tail_) {
    head_ = nullptr;
  }
  delete oldTail;
}

template< typename T >
bool odintsov::Stack< T >::empty() const
{
  return !tail_ || !head_;
}

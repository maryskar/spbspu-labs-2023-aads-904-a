#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H
#include <stdexcept>

template< typename T >
struct box {
  T value_ = 0;
  box< T >* prev_ = nullptr;
  box< T >* next_ = nullptr;
};

template< typename T >
class Queue {
public:
  Queue();
  ~Queue();
  void push(T rhs);
  T drop();
private:
  box< T >* head_ = nullptr;
  box< T >* tail_ = nullptr;
};

template< typename T >
Queue< T >::Queue():
  head_(nullptr),
  tail_(head_)
{}

template< typename T >
Queue< T >::~Queue()
{
  while (head_ != nullptr) {
    box< T >* next = head_->prev_;
    delete head_;
    head_ = next;
  }
}

template < typename T >
void Queue< T >::push(T rhs)
{
  box< T >* head = new box< T >{rhs, head_, nullptr};
  if (head_ == nullptr) {
    head_ = head;
    tail_ = head;
    return;
  }
  head_->next_ = head;
  head_ = head;
}

template <typename T >
T Queue< T >::drop()
{
  if (tail_ == nullptr) {
    throw std::length_error("Nothing to drop");
  }
  box< T >* next = tail_->next_;
  T res = tail_->value_;
  delete tail_;
  tail_ = next;
  return res;
}

#endif

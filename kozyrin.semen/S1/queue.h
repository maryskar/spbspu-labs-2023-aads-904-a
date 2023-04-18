#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>

template< typename T >
struct box_t {
  T value_ = 0;
  box_t< T >* prev_ = nullptr;
  box_t< T >* next_ = nullptr;
};

template< typename T >
class Queue {
public:
  Queue();
  ~Queue();
  void push(T rhs);
  T* drop();
  bool isEmpty();
private:
  box_t< T >* head_ = nullptr;
  box_t< T >* tail_ = nullptr;
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
    box_t< T >* next = head_->prev_;
    delete head_;
    head_ = next;
  }
}

template< typename T >
void Queue< T >::push(const T rhs)
{
  box_t< T >* head{rhs, head_, nullptr};
  if (head_ == nullptr) {
    head_ = head;
    tail_ = head;
    return;
  }
  head_->next_ = head;
  head_ = head;
}

template<typename T >
T* Queue< T >::drop()
{
  if (head_ == nullptr) {
    throw std::length_error("Nothing to drop");
  }

  box_t< T >* next = tail_->next_;
  T res = tail_->value_;
  tail_ = next;
  if (tail_ != nullptr) {
    tail_->prev_ = nullptr;
  } else {
    head_ = nullptr;
  }
  return res;
}

template< typename T >
bool Queue< T >::isEmpty()
{
  return head_ == nullptr;
}

#endif

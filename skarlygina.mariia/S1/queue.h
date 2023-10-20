#ifndef QUEUE_H
#define QUEUE_H
#include <cstddef>
#include <stdexcept>

namespace skarlygina
{
  template< typename T >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue< T >& other);
    Queue(Queue< T >&& other) noexcept;
    Queue< T >& operator=(const Queue< T >& other);
    Queue< T >& operator=(Queue< T >&& other);
    void push(const T& rhs);
    const T& top() const;
    void pop();
    bool isEmpty() const;
    ~Queue();
  private:
    struct List
    {
      T data;
      List* next;
    };
    List* head_;
    List* tail_;
  };

  template< typename T >
  Queue< T >::Queue():
    head_(nullptr),
    tail_(nullptr)
  {}

  template< typename T >
  Queue< T >::Queue(const Queue< T >& other):
    head_(nullptr),
    tail_(nullptr)
  {
    if (!other.isEmpty())
    {
      List* current = other.head_;
      while (current)
      {
        push(current->data);
        current = current->next;
      }
    }
  }

  template< typename T >
  Queue< T >::Queue(Queue< T >&& other) noexcept:
    head_(other.head_),
    tail_(other.tail_)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
  }

  template< typename T >
  Queue< T >& Queue< T >::operator=(Queue< T >& other)
  {
    if (this != std::addressof(other))
    {
      Queue< T > temp(other);
      std::swap(head_, temp.head_);
      std::swap(tail_, temp.tail_);
    }
    return *this;
  }

  template< typename T >
  Queue< T >& Queue< T >::operator=(Queue< T >&& other)
  {
    if (this != std::addressof(other))
    {
      head_ = std::move(other.head_);
      tail_ = other.tail_;
    }
    return *this;
  }

  template< typename T >
  void Queue< T >::push(const T& rhs)
  {
    List* new_node = new List{rhs, nullptr};
    if (isEmpty())
    {
      tail_ = head_ = new_node;
    }
    else
    {
      tail_->next = new_node;
      tail_ = tail_->next;
    }
  }

  template< typename T >
  void Queue< T >::pop()
  {
    if (isEmpty())
    {
      throw std::out_of_range("Queue is empty");
    }
    List* head_temp = head_;
    head_ = head_->next;
    delete head_temp;
  }

  template <class T>
  const T& Queue< T >::top() const
  {
    if (isEmpty())
    {
      throw std::runtime_error("Queue is empty");
    }
    return head_->data;
  }

  template< typename T >
  bool Queue< T >::isEmpty() const
  {
    return head_ == nullptr;
  }

  template< typename T >
  Queue< T >::~Queue()
  {
    while (head_ != nullptr)
    {
      List* temp = head_;
      head_ = head_->next;
      delete temp;
    }
    tail_ = nullptr;
  }
}
#endif

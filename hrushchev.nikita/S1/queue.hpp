#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "list.hpp"
#include <stdexcept>

template< typename T >
class Queue
{
  public:
    Queue();
    ~Queue();
    Queue(const Queue< T >& other);
    Queue< T >& operator=(const Queue< T >& other);
    Queue(Queue< T >&& other);
    Queue< T >& operator=(Queue < T >&& other);
    void push(const T& value);
    void pop();
    const T& get() const;
    bool isEmpty() const;
  private:
    List< T >* begin_;
    List< T >* end_;
};

template< typename T >
Queue< T >::Queue():
  begin_(nullptr),
  end_(nullptr)
{}

template< typename T >
bool Queue< T >::isEmpty() const
{
  return (begin_ == nullptr);
}

template< typename T >
void Queue< T >::push(const T& value)
{
  List< T >* temp = new List< T >{value, nullptr};
  if (isEmpty())
  {
    begin_ = temp;
  }
  else
  {
    end_->next = temp;
  }
  end_ = temp;
}

template< typename T >
const T& Queue< T >::get() const
{
  if(isEmpty())
  {
    throw std::logic_error("Empty queue");
  }
  return begin_->data;
}

template< typename T >
void Queue< T >::pop()
{
  if(isEmpty())
  {
    throw std::logic_error("Empty queue");
  }
  List< T >* temp = begin_->next;
  delete begin_;
  begin_ = temp;
}

template< typename T >
Queue< T >::~Queue()
{
  while(!isEmpty())
  {
    pop();
  }
}

template< typename T >
Queue< T >::Queue(const Queue< T >& other):
  begin_(nullptr),
  end_(nullptr)
{
  List< T >* curent = other.begin_;
  while (curent != nullptr)
  {
    push(curent->data);
    curent = curent->next;
  }
}

template< typename T >
Queue< T >& Queue< T >::operator=(const Queue< T >& other)
{
  if (this != &other)
  {
    while (!isEmpty())
    {
      pop();
    }
    List< T >* curent = other.begin_;
    while (curent != nullptr)
    {
      push(curent->data);
      curent = curent->next;
    }
  }
  return *this;
}

template < typename T >
Queue< T >::Queue(Queue< T >&& other):
  begin_(other.begin_),
  end_(other.end_)
{
  other.begin_ = nullptr;
  other.end_ = nullptr;
}

template < typename T >
Queue< T >& Queue< T >::operator=(Queue< T >&& other)
{
  if (this != other)
  {
    while (!isEmpty())
    {
      pop();
    }
    begin_ = other.begin_;
    other.begin_ = nullptr;
    end_ = other.end_;
    other.end_ = nullptr;
  }
}

#endif


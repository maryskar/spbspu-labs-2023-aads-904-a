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
    void push(const T& value);
    void pop();
    T& get() const;
    bool isEmpty() const;
  private:
    List< T >* begin_;
    List< T >* end_;
};

template< typename T >
Queue< T >::Queue():
begin_(nullptr),
end_(nullptr)
{
}

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
    end_->next_ = temp;
  }
  end_ = temp;
}

template< typename T >
T& Queue< T >::get() const
{
  if(isEmpty())
  {
    throw std::logic_error("Empty queue");
  }
  return begin_->data_;
}

template< typename T >
void Queue< T >::pop()
{
  if(isEmpty())
  {
    throw std::logic_error("Empty queue");
  }
  List< T >* temp = begin_->next_;
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

#endif
#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "list.hpp"

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
  List< T >* temp = new List< T >{end_, value};
  end_ = temp;
}
#endif
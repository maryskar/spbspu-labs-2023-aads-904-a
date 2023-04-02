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
    T& gete();
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


#endif
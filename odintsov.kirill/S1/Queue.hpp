#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Node.hpp"

namespace odintsov {
  template< typename T >
  class Queue {
   public:
    Queue();
    Queue(const Queue< T >& q);
    Queue(Queue< T >&& q);
    ~Queue();

    Queue< T >& operator=(const Queue< T >& q);
    Queue< T >& operator=(Queue< T >&& q);

    T& head();
    const T& head() const;
    void push(const T& data);
    void push(T&& data);
    void pop();
    bool empty() const;

   private:
    Node< T >* head_;
    Node< T >* tail_;

    void push(Node< T >* n);
  };
}

#include "Queue.tcc"

#endif

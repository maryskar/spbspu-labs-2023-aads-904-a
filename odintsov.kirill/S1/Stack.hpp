#ifndef STACK_HPP
#define STACK_HPP

#include "Node.hpp"

namespace odintsov {
  template< typename T >
  class Stack {
   public:
    Stack();
    Stack(const Stack< T >& s);
    Stack(Stack< T >&& s);
    ~Stack();

    Stack< T >& operator=(const Stack< T >& s);
    Stack< T >& operator=(Stack< T >&& s);

    T& tail();
    const T& tail() const;
    void push(const T& data);
    void push(T&& data);
    void pop();
    bool empty() const;

   private:
    detail::Node< T >* head_;
    detail::Node< T >* tail_;

    void push(detail::Node< T >* n);
  };
}

#include "Stack.tcc"

#endif

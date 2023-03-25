#ifndef STACK_HPP
#define STACK_HPP

namespace odintsov {
  template< typename T >
  class Stack {
   public:
    Stack();
    ~Stack();

    T& tail();
    const T& tail() const;
    void push(const T& data);
    void pop();
    bool empty() const;

   private:
    struct Node {
      T data;
      Node* prev;
    };

    Node* head_;
    Node* tail_;
  };
}

#include "Stack.tcc"

#endif

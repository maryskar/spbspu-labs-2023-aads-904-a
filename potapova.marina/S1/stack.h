#ifndef STACK_H
#define STACK_H

namespace potapova
{
  template< typename T >
  class Stack
  {
  public:
    Stack(): end_ptr(nullptr)
    {

    }

    ~Stack()
    {

    }

    void push(const T& elem)
    {

    }

    T drop()
    {

    }
  private:
    struct Node
    {
      Node(const T& data): data(data), prev_node_ptr(nullptr)
      {

      }
      
      T data;
      Node* prev_node_ptr;
    };
    Node* end_ptr;
  };
}

#endif

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
      while (end_ptr != nullptr)
      {
        pop();
      }
      
    }

    void push(const T& elem)
    {
      Node* new_end_ptr = new Node(elem);
      new_end_ptr->prev_node_ptr = end_ptr;
      end_ptr = new_end_ptr;
    }

    T& back()
    {
      return end_ptr->data;
    }

    void pop()
    {
      Node* prev_end_ptr = end_ptr;
      end_ptr = end_ptr->prev_node_ptr;
      delete prev_end_ptr;
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

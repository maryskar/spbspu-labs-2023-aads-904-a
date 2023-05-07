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

    T drop()
    {
      T prev_end_data = end_ptr->data;
      pop();
      return prev_end_data;
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

    void pop()
    {
      Node* prev_end_ptr = end_ptr;
      end_ptr = end_ptr->prev_node_ptr;
      delete prev_end_ptr;
    }
  };
}

#endif

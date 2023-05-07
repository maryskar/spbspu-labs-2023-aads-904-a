#ifndef QUEUE_H
#define QUEUE_H

namespace potapova
{
  template< typename T >
  class Queue
  {
  public:
    Queue(): begin_ptr(nullptr), end_ptr(nullptr)
    {

    }

    ~Queue()
    {
      while (begin_ptr != nullptr)
      {
        pop();
      }
    }

    void push(const T& elem)
    {
      if (begin_ptr == nullptr)
      {
        begin_ptr = end_ptr = new Node(elem);
        return;
      }
      end_ptr = end_ptr->next_node_ptr = new Node(elem);
    }

    T& front()
    {
      return begin_ptr->data;
    }

    void pop()
    {
      Node* prev_begin_ptr = begin_ptr;
      begin_ptr = begin_ptr->next_node_ptr;
      delete prev_begin_ptr;
    }
  private:
    struct Node
    {
      Node(const T& data): data(data), next_node_ptr(nullptr)
      {

      }

      T data;
      Node* next_node_ptr;
    };
    Node* begin_ptr;
    Node* end_ptr;
  };
}

#endif

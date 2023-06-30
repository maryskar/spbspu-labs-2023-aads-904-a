#ifndef QUEUE_H
#define QUEUE_H

namespace potapova
{
  template< typename T >
  class Queue
  {
  public:
    Queue():
      begin_ptr_(nullptr),
      end_ptr_(nullptr),
      size_(0)
    {

    }

    ~Queue()
    {
      while (!empty())
      {
        pop();
      }
    }

    Queue(const Queue& other): Queue()
    {
      Node* curr_node_ptr = other.begin_ptr_;
      while (curr_node_ptr != end_ptr_)
      {
        push(curr_node_ptr->data);
        curr_node_ptr = curr_node_ptr->next_node_ptr;
      }
    }

    void push(const T& elem)
    {
      if (begin_ptr_ == nullptr)
      {
        begin_ptr_ = end_ptr_ = new Node(elem);
      }
      else
      {
        end_ptr_ = end_ptr_->next_node_ptr = new Node(elem);
      }
      ++size_;
    }

    T& front()
    {
      return begin_ptr_->data;
    }

    void pop()
    {
      Node* prev_begin_ptr = begin_ptr_;
      begin_ptr_ = begin_ptr_->next_node_ptr;
      delete prev_begin_ptr;
      --size_;
    }

    size_t size() 
    {
      return size_;
    }

    bool empty()
    {
      return size_ == 0;
    }
  private:
    struct Node
    {
      Node(const T& data):
        data(data),
        next_node_ptr(nullptr)
      {

      }

      T data;
      Node* next_node_ptr;
    };
    Node* begin_ptr_;
    Node* end_ptr_;
    size_t size_;
  };
}

#endif

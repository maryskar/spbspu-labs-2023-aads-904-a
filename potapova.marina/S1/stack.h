#ifndef STACK_H
#define STACK_H

namespace potapova
{
  template< typename T >
  class Stack
  {
  public:
    Stack():
      end_ptr_(nullptr),
      size_(0)
    {

    }

    ~Stack()
    {
      while (end_ptr_ != nullptr)
      {
        pop();
      }
    }

    Stack(const Stack& other)
    {
      Node** cur_node_ptr_ptr = end_ptr_;
      Node** cur_other_node_ptr = other.end_ptr_;
      while (cur_other_node_ptr != nullptr)
      {
        *cur_node_ptr_ptr = new Node(cur_other_node_ptr_->data);
        cur_node_ptr_ptr = &(*cur_node_ptr_ptr)->prev_node_ptr;
        *cur_other_node_ptr = *cur_other_node_ptr->prev_node_ptr;
      }
      size_ = other.size_;
    }

    void push(const T& elem)
    {
      Node* new_end_ptr = new Node(elem);
      new_end_ptr->prev_node_ptr = end_ptr_;
      end_ptr_ = new_end_ptr;
      ++size_;
    }

    T& back()
    {
      return end_ptr_->data;
    }

    void pop()
    {
      Node* prev_end_ptr = end_ptr_;
      end_ptr_ = end_ptr_->prev_node_ptr;
      delete prev_end_ptr;
      --size_;
    }

    size_t size()
    {
      return size_;
    }

    bool empty()
    {
      return (size_ == 0);
    }
  private:
    struct Node
    {
      Node(const T& data):
        data(data),
        prev_node_ptr(nullptr)
      {

      }
      
      T data;
      Node* prev_node_ptr;
    };
    Node* end_ptr_;
    size_t size_ = 0;
  };
}

#endif

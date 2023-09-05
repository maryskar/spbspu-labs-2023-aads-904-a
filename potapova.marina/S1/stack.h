#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <utility>

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
      clear();
    }

    Stack(const Stack& other):
      Stack()
    {
      *this = other;
    }

    Stack(Stack&& other):
      Stack()
    {
      *this = std::move(other);
    }

    Stack& operator=(const Stack& other)
    {
      Node** cur_node_ptr_ptr = &end_ptr_;
      const Node* cur_other_node_ptr = other.end_ptr_;
      while (cur_other_node_ptr != nullptr)
      {
        if (*cur_node_ptr_ptr == nullptr)
        {
          *cur_node_ptr_ptr = new Node();
        }
        (*cur_node_ptr_ptr)->data = cur_other_node_ptr->data;
        cur_node_ptr_ptr = &((*cur_node_ptr_ptr)->prev_node_ptr);
        cur_other_node_ptr = cur_other_node_ptr->prev_node_ptr;
      }
      Node* extra_node_ptr = *cur_node_ptr_ptr;
      while (extra_node_ptr != nullptr)
      {
        Node* node_to_delete_ptr = extra_node_ptr;
        extra_node_ptr = extra_node_ptr->prev_node_ptr;
        delete node_to_delete_ptr;
      }
      *cur_node_ptr_ptr = nullptr;
      size_ = other.size_;
      return *this;
    }

    Stack& operator=(Stack&& other)
    {
      clear();
      end_ptr_ = other.end_ptr_;
      size_ = other.size_;
      other.end_ptr_ = nullptr;
      other.size_ = 0;
      return *this;
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

    const T& back() const
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

    size_t size() const
    {
      return size_;
    }

    bool empty() const
    {
      return (size_ == 0);
    }

    void clear()
    {
      while (!empty())
      {
        pop();
      }
    }
  private:
    struct Node
    {
      Node():
        data(),
        prev_node_ptr(nullptr)
      {

      }

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

#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include <cassert>
#include <memory>

namespace potapova
{
  template< typename T >
  class ForwardList
  {
    private:
      struct Node
      {
        Node():
          data(),
          next_node_ptr(nullptr)
        {

        }

        Node(const T& data):
          data(data),
          next_node_ptr(nullptr)
        {

        }

        T data;
        Node* next_node_ptr;
      };
    public:
      class ConstIterator
      {
        friend ForwardList;
        public:
          ConstIterator():
            node_ptr_(nullptr)
          {

          }

          ConstIterator(const Node* const node_ptr):
            node_ptr_(node_ptr)
          {

          }

          ~ConstIterator() = default;
          ConstIterator(const ConstIterator&) = default;
          ConstIterator& operator=(const ConstIterator&) = default;

          const ConstIterator& operator++()
          {
            assert(node_ptr_ != nullptr);
            node_ptr_ = node_ptr_->next_node_ptr;
            return *this;
          }

          ConstIterator operator++(int)
          {
            assert(node_ptr_ != nullptr);
            const ConstIterator result(*this);
            ++(*this);
            return result;
          }

          const T& operator*() const
          {
            assert(node_ptr_ != nullptr);
            return node_ptr_->data;
          }

          const T* operator->() const
          {
            assert(node_ptr_ != nullptr);
            return std::addressof(node_ptr_->data);
          }

          bool operator!=(const ConstIterator& rhs) const
          {
            return !(rhs == *this);
          }

          bool operator==(const ConstIterator& rhs) const
          {
            return node_ptr_ == rhs.node_ptr_;
          }
        private:
          const Node* node_ptr_; 
      };
      
      class Iterator
      {
        friend ForwardList;
        public:
          Iterator():
            node_ptr_(nullptr)
          {

          }

          Iterator(Node* const node_ptr):
            node_ptr_(node_ptr)
          {
            
          }

          ~Iterator() = default;
          Iterator(const Iterator&) = default;
          Iterator& operator=(const Iterator&) = default;

          Iterator& operator++()
          {
            assert(node_ptr_ != nullptr);
            node_ptr_ = node_ptr_->next_node_ptr;
            return *this;
          }

          Iterator operator++(int)
          {
            assert(node_ptr_ != nullptr);
            const Iterator result(*this);
            ++(*this);
            return result;
          }

          T& operator*()
          {
            assert(node_ptr_ != nullptr);
            return node_ptr_->data;
          }

          T* operator->()
          {
            assert(node_ptr_ != nullptr);
            return std::addressof(node_ptr_->data);
          }

          bool operator!=(const Iterator& rhs) const
          {
            return !(rhs == *this);
          }

          bool operator==(const Iterator& rhs) const
          {
            return node_ptr_ == rhs.node_;
          }
        private:
          Node* node_ptr_;
      };
    public:
      ForwardList():
        size_(0)
      {

      }

      ~ForwardList()
      {
        clear();
      }

      Iterator before_begin()
      {
        return Iterator(&head);
      }

      ConstIterator before_begin() const
      {
        return ConstIterator(&head);
      }

      Iterator begin()
      {
        return Iterator(head_.next_node_ptr);
      }

      ConstIterator begin() const
      {
        return ConstIterator(head_.next_node_ptr);
      }

      Iterator end()
      {
        return Iterator();
      }

      ConstIterator end() const
      {
        return ConstIterator();
      }

      T& front()
      {
        return *begin();
      }

      const T& front() const
      {
        return *cbegin();
      }

      void push_front(const T& value)
      {
        Node* new_node = new Node(value);
        new_node->next_node_ptr = head_;
        head_ = new_node; 
      }

      void clear()
      {
        while (head_ != nullptr)
        {
          Node* temp = head_;
          head_ = head_->next_node_ptr;
          delete temp;
        }
      }

      bool empty() const
      {
        return head_ == nullptr;
      }

      size_t size() const
      {
        size_t counter = 0;
        const Node* current = head_;
        while (current != nullptr)
        {
          ++counter;
          current = current->next_node_ptr;
        }
        return counter;
      }
    private:
      Node head_;
      size_t size_;
  };
}

#endif

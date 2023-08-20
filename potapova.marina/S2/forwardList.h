#ifndef FORWARDLIST_H
#define FORWARDLIST_H

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
      class Iterator
      {
        public:
          Iterator():
            node(nullptr)
          {

          }

          ~Iterator() = default;
          Iterator(const Iterator&) = default;
          Iterator& operator=(const Iterator&) = default;

          Iterator& operator++()
          {
            assert(node != nullptr);
            node = node->next;
          }

          Iterator operator++(int)
          {
            assert(node != nullptr);
            Iterator result(*this);
            ++(*this);
            return result;
          }

          T& operator*()
          {
            assert(node != nullptr);
            return node->data;
          }

          T* operator->()
          {
            assert(node != nullptr);
            return std::addressof(node->data);
          }

          bool operator!=(const Iterator& rhs) const
          {
            return !(rhs == *this);
          }

          bool operator==(const Iterator& rhs) const
          {
            return node == rhs.node;
          }
        private:
          Node* node;
      };

      class ConstIterator
      {
        public:
          ConstIterator():
            node(nullptr)
          {

          }

          ~ConstIterator() = default;
          ConstIterator(const ConstIterator&) = default;
          ConstIterator& operator=(const ConstIterator&) = default;

          const ConstIterator& operator++() const
          {
            assert(node != nullptr);
            node = node->next;
            return *this;
          }

          ConstIterator operator++(int) const
          {
            assert(node != nullptr);
            ConstIterator result(*this);
            ++(*this);
            return result;
          }

          const T& operator*() const
          {
            assert(node != nullptr);
            return node->data;
          }

          const T* operator->() const
          {
            assert(node != nullptr);
            return std::addressof(node->data);
          }

          bool operator!=(const ConstIterator& rhs) const
          {
            return !(rhs == *this);
          }

          bool operator==(const ConstIterator& rhs) const
          {
            return node == rhs.node;
          }
        private:
          const Node* node; 
      };

    public:
      ForwardList():
        head_(nullptr)
      {

      }

      ~ForwardList()
      {
        while (head_ != nullptr)
        {
          Node* temp = head_;
          head_ = head_->next_node_ptr;
          delete temp;
        }
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

      Iterator begin()
      {
        return Iterator(head_);
      }

      ConstIterator begin() const
      {
        return ConstIterator(head_);
      }

      Iterator end()
      {
        Node* last_node = head_;
        while (last_node != nullptr && last_node->next_node_ptr != nullptr)
        {
          last_node = last_node->next_node_ptr;
        }
        return Iterator(last_node);
      }

      ConstIterator end() const
      {
        Node* last_node = head_;
        while (last_node != nullptr || last_node->next_node_ptr != nullptr)
        {
          last_node = last_node->next_node_ptr;
        }
        return ConstIterator(last_node);
      }
    private:
      Node* head_;
  };
}

#endif

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

          bool operator==(const ConstIterator& rhs) const
          {
            return node_ptr_ == rhs.node_ptr_;
          }

          bool operator!=(const ConstIterator& rhs) const
          {
            return !(rhs == *this);
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

          bool operator==(const Iterator& rhs) const
          {
            return node_ptr_ == rhs.node_ptr_;
          }

          bool operator!=(const Iterator& rhs) const
          {
            return !(rhs == *this);
          }

          operator ConstIterator() const
          {
            return ConstIterator(node_ptr_);
          }
        private:
          Node* node_ptr_;
      };
    public:
      ForwardList():
        size_(0)
      {

      }

      ForwardList(const ForwardList& other)
      {
        *this = other;
      }

      ForwardList(ForwardList&& other)
      {
        *this = std::move(other);
      }

      ForwardList< T >& operator=(const ForwardList< T >& other)
      {
        if (!empty())
        {
          clear();
        }
        Iterator last_elem_ptr = before_begin();
        for (const T& cur_elem : other)
        {
          last_elem_ptr = insert_after(last_elem_ptr, cur_elem);
        }
        return *this;
      }

      ForwardList< T >& operator=(ForwardList< T >&& other)
      {
        if (!empty())
        {
          clear();
        }
        head_.data = std::move(other.head_.data);
        head_.next_node_ptr = other.head_.next_node_ptr;
        other.head_.next_node_ptr = nullptr;
        size_ = other.size_;
        return *this;
      }

      ~ForwardList()
      {
        clear();
      }

      Iterator before_begin()
      {
        return Iterator(&head_);
      }

      ConstIterator before_begin() const
      {
        return ConstIterator(&head_);
      }

      ConstIterator cbefore_begin() const
      {
        return ConstIterator(&head_);
      }

      Iterator begin()
      {
        return Iterator(head_.next_node_ptr);
      }

      ConstIterator begin() const
      {
        return ConstIterator(head_.next_node_ptr);
      }

      ConstIterator cbegin() const
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

      ConstIterator cend() const
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

      Iterator insert_after(const Iterator place_ptr, const T& value)
      {
        Node* const new_node_ptr = new Node(value);
	      new_node_ptr->next_node_ptr = place_ptr.node_ptr_->next_node_ptr;
	      place_ptr.node_ptr_->next_node_ptr = new_node_ptr;
        ++size_;
        return Iterator(new_node_ptr);
      }

      void push_front(const T& value)
      {
        insert_after(before_begin(), value); 
      }

      Iterator erase_after(const Iterator place_ptr)
      {
        Node* const deleted_node_ptr = place_ptr.node_ptr_->next_node_ptr;
        place_ptr.node_ptr_->next_node_ptr = deleted_node_ptr->next_node_ptr;
        delete deleted_node_ptr;
        --size_;
        return Iterator(place_ptr.node_ptr_->next_node_ptr);
      }

      void pop_front(const T& value)
      {
        erase_after(before_begin(), value);
      }

      void clear()
      {
        Node* cur_deleted_node_ptr = head_.next_node_ptr;
        while (cur_deleted_node_ptr != nullptr)
        {
          const Node* const temp = cur_deleted_node_ptr;
          cur_deleted_node_ptr = cur_deleted_node_ptr->next_node_ptr;
          delete temp;
        }
      }

      bool empty() const
      {
        return size_ == 0;
      }

      size_t size() const
      {
        return size_;
      }
    private:
      Node head_;
      size_t size_;
  };
}

#endif

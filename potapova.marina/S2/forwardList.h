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
      struct Node;
      
      struct NodeBase
      {
        NodeBase() noexcept:
          next_node_ptr_(nullptr)
        {

        }
        Node* next_node_ptr_;
      };

      struct Node: public NodeBase
      {
        Node(const T& data) noexcept:
          NodeBase(),
          data_(data)
        {

        }

        T data_;
      };
    public:
      class ConstIterator
      {
        friend ForwardList;
        public:
          ConstIterator() noexcept:
            node_ptr_(nullptr)
          {

          }

          ConstIterator(const NodeBase* const node_ptr) noexcept:
            node_ptr_(node_ptr),
            data_ptr(nullptr)
          {

          }

          ConstIterator(const Node* const node_ptr) noexcept:
            node_ptr_(node_ptr),
            data_ptr(std::addressof(node_ptr->data_))
          {

          }

          ~ConstIterator() noexcept = default;
          ConstIterator(const ConstIterator&) noexcept = default;
          ConstIterator& operator=(const ConstIterator&) noexcept = default;

          const ConstIterator& operator++() noexcept
          {
            assert(node_ptr_ != nullptr);
            if (node_ptr_->next_node_ptr_ != nullptr)
            {
              data_ptr = std::addressof(node_ptr_->next_node_ptr_->data_);
            }
            node_ptr_ = node_ptr_->next_node_ptr_;
            return *this;
          }

          ConstIterator operator++(int) noexcept
          {
            assert(node_ptr_ != nullptr);
            const ConstIterator result(*this);
            ++(*this);
            return result;
          }

          const T& operator*() const noexcept
          {
            assert(node_ptr_ != nullptr);
            assert(data_ptr != nullptr);
            return *data_ptr;
          }

          const T* operator->() const noexcept
          {
            assert(node_ptr_ != nullptr);
            assert(data_ptr != nullptr);
            return data_ptr;
          }

          bool operator==(const ConstIterator& rhs) const noexcept
          {
            return node_ptr_ == rhs.node_ptr_;
          }

          bool operator!=(const ConstIterator& rhs) const noexcept
          {
            return !(rhs == *this);
          }
        private:
          const NodeBase* node_ptr_;
          const T* data_ptr;
      };

      class Iterator
      {
        friend ForwardList;
        public:
          Iterator() noexcept:
            node_ptr_(nullptr)
          {

          }

          Iterator(NodeBase* const node_ptr) noexcept:
            node_ptr_(node_ptr),
            data_ptr(nullptr)
          {

          }

          Iterator(Node* const node_ptr) noexcept:
            node_ptr_(node_ptr),
            data_ptr(std::addressof(node_ptr->data_))
          {

          }

          ~Iterator() noexcept = default;
          Iterator(const Iterator&) noexcept = default;
          Iterator& operator=(const Iterator&) noexcept = default;

          Iterator& operator++() noexcept
          {
            assert(node_ptr_ != nullptr);
            if (node_ptr_->next_node_ptr_ != nullptr)
            {
              data_ptr = std::addressof(node_ptr_->next_node_ptr_->data_);
            }
            node_ptr_ = node_ptr_->next_node_ptr_;
            return *this;
          }

          Iterator operator++(int) noexcept
          {
            assert(node_ptr_ != nullptr);
            const Iterator result(*this);
            ++(*this);
            return result;
          }

          T& operator*() noexcept
          {
            assert(node_ptr_ != nullptr);
            assert(data_ptr != nullptr);
            return *data_ptr;
          }

          T* operator->() const noexcept
          {
            assert(node_ptr_ != nullptr);
            assert(data_ptr != nullptr);
            return data_ptr;
          }

          bool operator==(const Iterator& rhs) const noexcept
          {
            return node_ptr_ == rhs.node_ptr_;
          }

          bool operator!=(const Iterator& rhs) const noexcept
          {
            return !(rhs == *this);
          }

          operator ConstIterator() const noexcept
          {
            return ConstIterator(node_ptr_);
          }
        private:
          NodeBase* node_ptr_;
          T* data_ptr;
      };
    public:
      ForwardList() noexcept:
        size_(0)
      {

      }

      ForwardList(const ForwardList& other):
        ForwardList()
      {
        *this = other;
      }

      ForwardList(ForwardList&& other) noexcept:
        ForwardList()
      {
        *this = std::move(other);
      }

      ForwardList< T >& operator=(const ForwardList< T >& other)
      {
        Iterator cur_elem_ptr = begin();
        ConstIterator cur_other_elem_ptr = other.begin();
        Iterator prev_elem_ptr = before_begin();
        while (cur_elem_ptr != end())
        {
          if (cur_other_elem_ptr == other.end())
          {
            cur_elem_ptr = erase_after(prev_elem_ptr);
          }
          else
          {
            *cur_elem_ptr = *cur_other_elem_ptr;
            ++cur_other_elem_ptr;
            prev_elem_ptr = cur_elem_ptr;
            ++cur_elem_ptr;
          }
        }
        Iterator& last_elem_ptr = prev_elem_ptr;
        for (; cur_other_elem_ptr != other.end(); ++cur_other_elem_ptr)
        {
          last_elem_ptr = insert_after(last_elem_ptr, *cur_other_elem_ptr);
        }
        return *this;
      }

      ForwardList< T >& operator=(ForwardList< T >&& other) noexcept
      {
        if (!empty())
        {
          clear();
        }
        head_.next_node_ptr_ = other.head_.next_node_ptr_;
        other.head_.next_node_ptr_ = nullptr;
        size_ = other.size_;
        return *this;
      }

      ~ForwardList() noexcept
      {
        clear();
      }

      Iterator before_begin() noexcept
      {
        return Iterator(std::addressof(head_));
      }

      ConstIterator before_begin() const noexcept
      {
        return ConstIterator(std::addressof(head_));
      }

      ConstIterator cbefore_begin() const noexcept
      {
        return ConstIterator(std::addressof(head_));
      }

      Iterator begin() noexcept
      {
        return Iterator(head_.next_node_ptr_);
      }

      ConstIterator begin() const noexcept
      {
        return ConstIterator(head_.next_node_ptr_);
      }

      ConstIterator cbegin() const noexcept
      {
        return ConstIterator(head_.next_node_ptr_);
      }

      Iterator end() noexcept
      {
        return Iterator();
      }

      ConstIterator end() const noexcept
      {
        return ConstIterator();
      }

      ConstIterator cend() const noexcept
      {
        return ConstIterator();
      }

      T& front() noexcept
      {
        return *begin();
      }

      const T& front() const noexcept
      {
        return *cbegin();
      }

      Iterator insert_after(const Iterator place_ptr, const T& value)
      {
        Node* const new_node_ptr = new Node(value);
        new_node_ptr->next_node_ptr_ = place_ptr.node_ptr_->next_node_ptr_;
        place_ptr.node_ptr_->next_node_ptr_ = new_node_ptr;
        ++size_;
        return Iterator(new_node_ptr);
      }

      void push_front(const T& value)
      {
        insert_after(before_begin(), value);
      }

      Iterator erase_after(const Iterator place_ptr) noexcept
      {
        Node* const deleted_node_ptr = place_ptr.node_ptr_->next_node_ptr_;
        place_ptr.node_ptr_->next_node_ptr_ = deleted_node_ptr->next_node_ptr_;
        delete deleted_node_ptr;
        --size_;
        return Iterator(place_ptr.node_ptr_->next_node_ptr_);
      }

      void pop_front() noexcept
      {
        erase_after(before_begin());
      }

      void clear() noexcept
      {
        Node* cur_deleted_node_ptr = head_.next_node_ptr_;
        while (cur_deleted_node_ptr != nullptr)
        {
          const Node* const temp = cur_deleted_node_ptr;
          cur_deleted_node_ptr = cur_deleted_node_ptr->next_node_ptr_;
          delete temp;
        }
      }

      bool empty() const noexcept
      {
        return size_ == 0;
      }

      size_t size() const noexcept
      {
        return size_;
      }
    private:
      NodeBase head_;
      size_t size_;
  };
}

#endif

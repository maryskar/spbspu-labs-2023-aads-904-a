#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <stdexcept>
#include <tuple>

#include "Node.hpp"

namespace odintsov {
  template< typename T >
  class Queue {
   public:
    Queue():
      head_(nullptr),
      tail_(nullptr)
    {}

    Queue(const Queue< T >& q):
      head_(nullptr),
      tail_(nullptr)
    {
      std::tie(head_, tail_) = detail::duplicateNodes(q.head_);
    }

    Queue(Queue< T >&& q):
      head_(q.head_),
      tail_(q.tail_)
    {
      q.head_ = nullptr;
      q.tail_ = nullptr;
    }

    ~Queue()
    {
      detail::deleteNodes(head_);
    }

    Queue< T >& operator=(const Queue< T >& q)
    {
      if (this == &q) {
        return *this;
      }
      detail::Node< T >* oldHead = head_;
      std::tie(head_, tail_) = detail::duplicateNodes(q.head_);
      detail::deleteNodes(oldHead);
      return *this;
    }

    Queue< T >& operator=(Queue< T >&& q)
    {
      detail::deleteNodes(head_);
      head_ = q.head_;
      tail_ = q.tail_;
      q.head_ = nullptr;
      q.tail_ = nullptr;
      return *this;
    }

    const T& head() const
    {
      if (empty()) {
        throw std::runtime_error("Attempt to get head of empty queue");
      }
      return head_->data;
    }

    T& head()
    {
      return const_cast< T& >(const_cast< const Queue< T >* >(this)->head());
    }

    void push(const T& data)
    {
      push(new detail::Node< T >{data, nullptr});
    }

    void push(T&& data)
    {
      push(new detail::Node< T >{data, nullptr});
    }

    void pop()
    {
      if (empty()) {
        throw std::runtime_error("Attempt to pop empty queue");
      }
      detail::Node< T >* oldHead = head_;
      head_ = head_->next;
      if (!head_) {
        tail_ = nullptr;
      }
      delete oldHead;
    }

    bool empty() const
    {
      return !head_ || !tail_;
    }

   private:
    detail::Node< T >* head_;
    detail::Node< T >* tail_;

    void push(detail::Node< T >* n)
    {
      if (empty()) {
        head_ = n;
      } else {
        tail_->next = n;
      }
      tail_ = n;
    }
  };
}

#endif

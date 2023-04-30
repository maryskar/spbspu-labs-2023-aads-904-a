#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <memory>
#include <stdexcept>
#include <tuple>

#include "Node.hpp"

namespace odintsov {
  template< typename T >
  class Queue {
   public:
    Queue():
      headTail_(nullptr, nullptr)
    {}

    Queue(const Queue< T >& q):
      headTail_(detail::duplicateNodes(q.headTail_.first))
    {}

    Queue(Queue< T >&& q):
      headTail_(nullptr, nullptr)
    {
      headTail_.swap(q.headTail_);
    }

    ~Queue()
    {
      detail::deleteNodes(headTail_.first);
    }

    Queue< T >& operator=(const Queue< T >& q)
    {
      if (this == std::addressof(q)) {
        return *this;
      }
      detail::Node< T >* oldHead = headTail_.first;
      headTail_ = detail::duplicateNodes(q.head_);
      detail::deleteNodes(oldHead);
      return *this;
    }

    Queue< T >& operator=(Queue< T >&& q)
    {
      detail::deleteNodes(headTail_.first);
      headTail_ = q.headTail_;
      q.headTail_.first = nullptr;
      q.headTail_.second = nullptr;
      return *this;
    }

    const T& head() const
    {
      if (empty()) {
        throw std::runtime_error("Attempt to get head of empty queue");
      }
      return headTail_.first->data;
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
      push(new detail::Node< T >{std::move(data), nullptr});
    }

    void pop()
    {
      if (empty()) {
        throw std::runtime_error("Attempt to pop empty queue");
      }
      detail::Node< T >* oldHead = headTail_.first;
      headTail_.first = headTail_.first->next;
      if (!headTail_.first) {
        headTail_.second = nullptr;
      }
      delete oldHead;
    }

    bool empty() const
    {
      return !headTail_.first;
    }

   private:
    std::pair< detail::Node< T >*, detail::Node< T >* > headTail_;

    void push(detail::Node< T >* n)
    {
      if (empty()) {
        headTail_.first = n;
      } else {
        headTail_.second->next = n;
      }
      headTail_.second = n;
    }
  };
}

#endif

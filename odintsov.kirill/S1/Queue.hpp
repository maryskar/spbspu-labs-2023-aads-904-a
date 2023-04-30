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
      boundPtrs_(nullptr, nullptr)
    {}

    Queue(const Queue< T >& q):
      boundPtrs_(detail::duplicateNodes(*q.headPtr()))
    {}

    Queue(Queue< T >&& q):
      boundPtrs_(nullptr, nullptr)
    {
      boundPtrs_.swap(q.boundPtrs_);
    }

    ~Queue()
    {
      detail::deleteNodes(*headPtr());
    }

    Queue< T >& operator=(const Queue< T >& q)
    {
      if (this == std::addressof(q)) {
        return *this;
      }
      detail::Node< T >* oldHead = *headPtr();
      boundPtrs_ = detail::duplicateNodes(q.head_);
      detail::deleteNodes(oldHead);
      return *this;
    }

    Queue< T >& operator=(Queue< T >&& q)
    {
      detail::Node< T >** head = headPtr();
      detail::deleteNodes(*head);
      boundPtrs_ = q.boundPtrs_;
      *q.headPtr() = nullptr;
      *q.tailPtr() = nullptr;
      return *this;
    }

    const T& head() const
    {
      if (empty()) {
        throw std::runtime_error("Attempt to get head of empty queue");
      }
      return (*headPtr())->data;
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
      detail::Node< T >** head = headPtr();
      detail::Node< T >* oldHead = *head;
      *head = (*head)->next;
      if (!*head) {
        *tailPtr() = nullptr;
      }
      delete oldHead;
    }

    bool empty() const
    {
      return !*headPtr();
    }

   private:
    std::pair< detail::Node< T >*, detail::Node< T >* > boundPtrs_;

    detail::Node< T >** headPtr()
    {
      return std::addressof(boundPtrs_.first);
    }

    const detail::Node< T >* const* headPtr() const
    {
      return const_cast< const detail::Node< T >* const* >(std::addressof(boundPtrs_.first));
    }

    detail::Node< T >** tailPtr()
    {
      return std::addressof(boundPtrs_.second);
    }

    const detail::Node< T >* const* tailPtr() const
    {
      return const_cast< const detail::Node< T >* const* >(std::addressof(boundPtrs_.second));
    }

    void push(detail::Node< T >* n)
    {
      if (empty()) {
        *headPtr() = n;
      } else {
        (*tailPtr())->next = n;
      }
      *tailPtr() = n;
    }
  };
}

#endif

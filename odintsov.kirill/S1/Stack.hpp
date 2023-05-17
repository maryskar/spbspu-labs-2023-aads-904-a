#ifndef STACK_HPP
#define STACK_HPP

#include <memory>
#include <stdexcept>

#include "Node.hpp"

namespace odintsov {
  template< typename T >
  class Stack {
   public:
    Stack():
      tail_(nullptr)
    {}

    Stack(const Stack< T >& s):
      tail_(nullptr)
    {
      tail_ = detail::duplicateNodes(s.tail_).first;
    }

    Stack(Stack< T >&& s):
      tail_(s.tail_)
    {
      s.tail_ = nullptr;
    }

    ~Stack()
    {
      detail::deleteNodes(tail_);
    }

    Stack< T >& operator=(const Stack< T >& s)
    {
      if (this == std::addressof(s)) {
        return *this;
      }
      detail::Node< T >* oldTail = tail_;
      tail_ = detail::duplicateNodes(s.tail_).first;
      detail::deleteNodes(oldTail);
      return *this;
    }

    Stack< T >& operator=(Stack< T >&& s)
    {
      detail::deleteNodes(tail_);
      tail_ = s.tail_;
      s.tail_ = nullptr;
      return *this;
    }

    const T& tail() const
    {
      if (empty()) {
        throw std::runtime_error("Attempt to get tail of empty stack");
      }
      return tail_->data;
    }

    T& tail()
    {
      return const_cast< T& >(const_cast< const Stack< T >* >(this)->tail());
    }

    void push(const T& data)
    {
      push(new detail::Node< T >{data, tail_});
    }

    void push(T&& data)
    {
      push(new detail::Node< T >{std::move(data), tail_});
    }

    void pop()
    {
      if (empty()) {
        throw std::runtime_error("Attempt to pop empty stack");
      }
      detail::Node< T >* oldTail = tail_;
      tail_ = tail_->next;
      delete oldTail;
    }

    bool empty() const
    {
      return !tail_;
    }

   private:
    detail::Node< T >* tail_;

    void push(detail::Node< T >* n)
    {
      tail_ = n;
    }
  };
}

#endif

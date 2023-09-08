#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include "forwardList.h"

namespace potapova
{
  template< typename T >
  class Stack
  {
  public:
    void push(const T& elem)
    {
      data_.push_front(elem);
    }

    T& top()
    {
      return data_.front();
    }

    const T& top() const
    {
      return data_.front();
    }

    void pop()
    {
      data_.pop_front();
    }

    size_t size() const
    {
      return data_.size();
    }

    bool empty() const
    {
      return data_.empty();
    }

    void clear()
    {
      data_.clear();
    }
  private:
    ForwardList< T > data_;
  };
}

#endif

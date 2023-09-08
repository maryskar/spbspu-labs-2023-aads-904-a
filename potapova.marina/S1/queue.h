#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
#include "forwardList.h"

namespace potapova
{
  template< typename T >
  class Queue
  {
    public:
      void push(const T& elem)
      {
        data_.push_front(elem);
      }

      T& front()
      {
        return data_.front();
      }

      const T& front() const
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
    private:
      ForwardList< T > data_;
  };
}

#endif

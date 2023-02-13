#ifndef SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#define SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#include <cstddef>
#include <stdexcept>
#include <list>
#include "expand.h"
#include "container.h"
namespace dimkashelk
{
  template < typename T >
  class Queue: Container< T >
  {
  public:
    Queue()
    {}
    Queue< T > (const Queue< T > &queue):
      data_(queue.data_)
    {}
    void push(T rhs)
    {
      data_.push_back(rhs);
    }
    T drop()
    {
      T obj = data_.front();
      data_.pop_front();
      return obj;
    }
    bool empty() const
    {
      return data_.size() == 0;
    }
  private:
    std::list< T > data_;
  };
}
#endif

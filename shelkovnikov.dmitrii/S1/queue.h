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
      data(queue.data)
    {}
    ~Queue()
    {
      delete data;
    }
    void push(T rhs)
    {
      data.push_back(rhs);
    }
    T drop()
    {
      T obj = data.front();
      data.pop_front();
      return obj;
    }
    bool empty() const
    {
      return data.size() == 0;
    }
  private:
    std::list< T > data;
  };
}
#endif

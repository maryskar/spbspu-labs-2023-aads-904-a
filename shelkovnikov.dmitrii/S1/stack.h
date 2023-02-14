#ifndef SPBSPU_LABS_2023_AADS_904_A_STACK_H
#define SPBSPU_LABS_2023_AADS_904_A_STACK_H
#include <cstddef>
#include <stdexcept>
#include <list>
#include "expand.h"
namespace dimkashelk
{
  template < typename T >
  class Stack
  {
  public:
    Stack()
    {}
    void push(T rhs)
    {
      data_.push_back(rhs);
    }
    T drop()
    {
      if (data_.size() == 0)
      {
        throw std::logic_error("Check");
      }
      T obj = data_.back();
      data_.pop_back();
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

#ifndef SPBSPU_LABS_2023_AADS_904_A_STACK_H
#define SPBSPU_LABS_2023_AADS_904_A_STACK_H
#include <cstddef>
#include <stdexcept>
#include <list>
#include "expand.h"
#include "container.h"
namespace dimkashelk
{
  template < typename T >
  class Stack: public Container< T >
  {
  public:
    Stack()
    {}
    ~Stack()
    {
      delete data;
    }
    void push(T rhs)
    {
      data.push_back(rhs);
    }
    T drop()
    {
      if (data.size() == 0)
      {
        throw std::logic_error("Check");
      }
      T obj = data.back();
      data.pop_back();
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

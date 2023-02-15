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
    Stack():
      begin_(nullptr)
    {}
    ~Stack()
    {
      while (begin_)
      {
        drop();
      }
    }
    void push(T rhs)
    {
      Node< T > *node = new Node< T >(rhs);
      if (empty())
      {
        begin_ = node;
      }
      else
      {
        Node< T > *last = begin_;
        while (last->next_)
        {
          last = last->next_;
        }
        last->next_ = node;
      }
    }
    T drop()
    {
      if (empty())
      {
        throw std::logic_error("Check");
      }
      Node< T > *cur = begin_;
      Node< T > *last = nullptr;
      while (cur->next_)
      {
        last = cur;
        cur = cur->next_;
      }
      T data = cur->data_;
      if (last == nullptr)
      {
        delete begin_;
        begin_ = nullptr;
      }
      else
      {
        delete cur;
        last->next_ = nullptr;
      }
      return data;
    }
    bool empty() const
    {
      return begin_ == nullptr;
    }
  private:
    Node< T > *begin_;
  };
}
#endif

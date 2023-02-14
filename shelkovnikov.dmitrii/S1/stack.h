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
      begin(nullptr)
    {}
    void push(T rhs)
    {
      Node *node = new Node(rhs);
      if (empty())
      {
        begin = node;
      }
      else
      {
        Node *last = begin;
        while (last->next)
        {
          last = last->next;
        }
        last->next = node;
      }
    }
    T drop()
    {
      if (empty())
      {
        throw std::logic_error("Check");
      }
      Node *cur = begin;
      Node *last = nullptr;
      while (cur->next)
      {
        last = cur;
        cur = cur->next;
      }
      T data = cur->data;
      if (last == nullptr)
      {
        delete begin;
        begin = nullptr;
      }
      else
      {
        delete cur;
        last->next = nullptr;
      }
      return data;
    }
    bool empty() const
    {
      return begin == nullptr;
    }
  private:
    struct Node
    {
      T data;
      Node *next;
      explicit Node(T rhs):
        data(rhs),
        next(nullptr)
      {}
    };
    Node *begin;
  };
}
#endif

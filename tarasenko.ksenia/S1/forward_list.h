#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include <memory>
#include "node.h"
namespace tarasenko
{
  template< typename T >
  class ForwardList
  {
  public:
   ForwardList():
     first(nullptr)
   {};

   ForwardList(const ForwardList< T >& other):
     first(nullptr)
   {
     ForwardList< T >* copy = other.first;
     while (copy)
     {
       pushBack(std::addressof(first), copy->data);
       copy = copy->next;
     }
   }
   ForwardList(ForwardList< T >&& other):
     first(other.first)
   {
     other.first = nullptr;
   }
   ForwardList< T >& operator=(const ForwardList< T >& q)
   {}
   ForwardList< T >& operator=(ForwardList< T >&& q)
   {}
   ~ForwardList()
   {
     details::clear(std::addressof(first));
   };

  private:
   details::NodeOfList< T >* first;
  };
}
#endif

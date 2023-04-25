#ifndef NODE_H
#define NODE_H
#include "operations.h"
#include "parenthesis.h"
#include <stdexcept>
namespace details
{
  template < typename T >
  struct ListNode
  {
    T data_;
    ListNode< T > *next_;
  };

  template < typename T >
  void clear(ListNode< T > *pNode)
  {
    while (pNode)
    {
      ListNode< T > *nextNode = pNode->next_;
      delete pNode;
      pNode = nextNode;
    }
  }
}
#endif

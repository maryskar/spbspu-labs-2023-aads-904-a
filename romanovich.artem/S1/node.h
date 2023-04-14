#ifndef NODE_H
#define NODE_H
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
    while (*pNode)
    {
      ListNode< T > *p = pNode;
      pNode = p->next;
      delete p;
    }
    pNode = nullptr;
  }
}
#endif

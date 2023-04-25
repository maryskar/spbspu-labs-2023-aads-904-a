#ifndef LISTNODE_H
#define LISTNODE_H
#include <stdexcept>
namespace details
{
  template < typename T >
  struct ListNode
  {
    T data_;
    ListNode< T > *next_;
  };
}
#endif

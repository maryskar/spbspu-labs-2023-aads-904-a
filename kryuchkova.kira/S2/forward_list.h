#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include <iterator>
#include <initializer_list>
#include "forward_list_const_iterator.h"
#include "forward_list_iterator.h"

namespace kryuchkova
{
  template< typename T >
  class ForwardList
  {
  public:
    using iterator = ForwardIterator< T >;
    using const_iterator = ConstForwardIterator< T >;
    using this_t = ForwardList< T >;
    ForwardList();
    ForwardList(const this_t & rhs);
    ForwardList(this_t && rhs);
    ForwardList(std::initializer_list< T > init);
    ~ForwardList();
  };
}

#endif

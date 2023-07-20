#ifndef LIST_HPP
#define LIST_HPP

namespace details
{
  template < typename T >
  struct List
  {
    T data;
    List< T >* next;
  };
}

#endif


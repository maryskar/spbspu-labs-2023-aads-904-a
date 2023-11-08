#ifndef LIST_H
#define LIST_H

namespace chulkov {
  template < typename T >
  struct List
  {
    T data;
    List< T >* next;
  };
}

#endif

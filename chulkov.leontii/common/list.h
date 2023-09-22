#ifndef LIST_H
#define LIST_H

namespace chulkov {
  template < typename T >
  struct List
  {
    T item_;
    List< T >* next_;
  };
}

#endif

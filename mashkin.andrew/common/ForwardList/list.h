#ifndef LIST_H
#define LIST_H

namespace mashkin
{
  template< typename T >
  struct list_t
  {
    T data;
    list_t< T >* next;
  };
}
#endif

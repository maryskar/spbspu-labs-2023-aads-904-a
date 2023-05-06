#ifndef LIST_H
#define LIST_H

namespace mashkin
{
  template< typename T >
  struct list_t
  {
    T data;
    list_t< T >* next;
    void clear();
  };
}

template< typename T >
void mashkin::list_t< T >::clear()
{
  list_t< T >* current = this;
  while (current != nullptr)
  {
    list_t< T >* next = current->next;
    delete current;
    current = next;
  }
}
#endif

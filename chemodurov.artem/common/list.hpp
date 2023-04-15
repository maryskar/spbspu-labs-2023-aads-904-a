#ifndef LIST_HPP
#define LIST_HPP

namespace chemodurov
{
  template< typename T >
  struct List
  {
    T data;
    List< T > * next;
  };

  template< typename T >
  void deleteList(List< T > * head)
  {
    while (head)
    {
      List< T > * temp = head->next;
      delete head;
      head = temp;
    }
  }
}

#endif

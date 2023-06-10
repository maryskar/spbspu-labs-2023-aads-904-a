#ifndef LIST_H
#define LIST_H
namespace aksenov {
  template< typename T >
  struct List
  {
    T data;
    List< T > *next;
  };

  template< typename T>
  void deleteList(List< T > *head)
  {
    while(head)
    {
      auto todel = head;
      head = head->next;
      delete todel;
    }
  }
}
#endif

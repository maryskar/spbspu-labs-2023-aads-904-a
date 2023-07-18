#ifndef LIST_H
#define LIST_H
namespace fesenko
{
  template < typename T >
  struct List
  {
    T data;
    List< T > *next;
  };

  template < typename T >
  void deleteList(List< T > *head)
  {
    while (head) {
      List< T > *temp = head->next;
      delete head;
      head = temp;
    }
    head = nullptr;
  }
}
#endif

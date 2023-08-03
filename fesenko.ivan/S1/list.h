#ifndef LIST_H
#define LIST_H
#include <utility>
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

  template< typename T >
  std::pair< List< T > *, List< T > * > copyList(const List< T > *head)
  {
    if (head == nullptr) {
      return {nullptr, nullptr};
    }
    List< T > *newHead = nullptr;
    try {
      newHead = new List< T > {head->data, nullptr};
      head = head->next;
      auto *cur = newHead;
      while (head) {
        cur->next = new List< T > {head->data, nullptr};
        cur = cur->next;
        head = head->next;
      }
      return {newHead, cur};
    } catch (...) {
      deleteList(newHead);
      throw;
    }
  }
}
#endif

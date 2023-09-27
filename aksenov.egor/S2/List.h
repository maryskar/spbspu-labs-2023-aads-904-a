#ifndef LIST_H
#define LIST_H
namespace aksenov
{
  template< typename T >
  struct listT
  {
    T data;
    listT< T > *next;
  };

  template< typename T >
  std::pair< listT< T > *, listT< T > * > copyList(const listT< T > *head)
  {
    if (head == nullptr) {
      return {nullptr, nullptr};
    }
    listT< T > *newHead = nullptr;
    try {
      newHead = new listT< T > {head->data, nullptr};
      head = head->next;
      auto *cur = newHead;
      while (head) {
        cur->next = new listT< T > {head->data, nullptr};
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

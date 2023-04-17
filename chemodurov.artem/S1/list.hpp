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

  template< typename T >
  std::pair< List< T > *, List< T > * > copyList(const List< T > * head)
  {
    if (!head)
    {
      return {nullptr, nullptr};
    }

    List< T > * source = head;
    List< T > * dest = new List< T >{source->data, nullptr};
    List< T > * temp = dest;
    List< T > * dest_last = temp;
    try
    {
      while (source->next)
      {
        source = source->next;
        dest_last = temp;
        temp->next = new List< T >{source->data, nullptr};
        temp = temp->next;
      }
    }
    catch (...)
    {
      deleteList(dest);
      throw;
    }
    return {dest, dest_last};
  }
}

#endif

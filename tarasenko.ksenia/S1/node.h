#ifndef NODE_H
#define NODE_H
namespace tarasenko
{
  namespace details
  {
    template< typename T >
    struct NodeOfList
    {
      NodeOfList(T& data, NodeOfList< T >* next) :
        data(data),
        next(next)
      {}

      T data;
      NodeOfList< T >* next;
    };

    template< typename T >
    bool isEmpty(NodeOfList< T >* list)
    {
      return list == nullptr;
    }

    template< typename T >
    void pushFront(NodeOfList< T >** plist, T& d)
    {
      *plist = new NodeOfList< T >(d, *plist);
    }

    template< typename T >
    void pushBack(NodeOfList< T >** plist, T& data)
    {
      if (*plist == nullptr)
      {
        *plist = new NodeOfList< T >(data, nullptr);
      }
      else
      {
        NodeOfList< T >* current = *plist;

        while (current->next != nullptr)
        {
          current = current->next;
        }
        current->next = new NodeOfList< T >(data, nullptr);
      }
    }

    template< typename T >
    T getFront(NodeOfList< T >* list)
    {
      T res = list->data;
      return res;
    }

    template< typename T >
    void popFront(NodeOfList< T >** plist)
    {
      NodeOfList< T >* p = *plist;
      *plist = p->next;
      delete p;
    }

    template< typename T >
    void clear(NodeOfList< T >** plist)
    {
      while (*plist)
      {
        details::popFront(plist);
      }
      *plist = nullptr;
    }
  };
}
#endif

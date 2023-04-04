#ifndef NODE_H
#define NODE_H
namespace tarasenko
{
  namespace details
  {
    template< typename T >
    struct NodeOfList
    {
      NodeOfList(const T& data, NodeOfList< T >* next) :
        data(data),
        next(next)
      {}

      T data;
      NodeOfList< T >* next;
    };

    template< typename T >
    bool isEmpty(NodeOfList< T >* node)
    {
      return node == nullptr;
    }

    template< typename T >
    void pushFront(NodeOfList< T >** pnode, T& d)
    {
      *pnode = new NodeOfList< T >(d, *pnode);
    }

    template< typename T >
    void pushBack(NodeOfList< T >** pnode, T& data)
    {
      if (*pnode == nullptr)
      {
        *pnode = new NodeOfList< T >(data, nullptr);
      }
      else
      {
        NodeOfList< T >* current = *pnode;

        while (current->next != nullptr)
        {
          current = current->next;
        }
        current->next = new NodeOfList< T >(data, nullptr);
      }
    }

    template< typename T >
    T getFront(NodeOfList< T >* node)
    {
      T res = node->data;
      return res;
    }

    template< typename T >
    void popFront(NodeOfList< T >** pnode)
    {
      NodeOfList< T >* p = *pnode;
      *pnode = p->next;
      delete p;
    }

    template< typename T >
    void clear(NodeOfList< T >** pnode)
    {
      while (*pnode)
      {
        details::popFront(pnode);
      }
      *pnode = nullptr;
    }
  };
}
#endif

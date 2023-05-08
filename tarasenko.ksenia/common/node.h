#ifndef NODE_H
#define NODE_H
#include <memory>
namespace tarasenko
{
  namespace details
  {
    template< typename T >
    struct NodeOfList
    {
      NodeOfList(const T& data, NodeOfList< T >* next):
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
    void pushFront(NodeOfList< T >** pnode, const T& d)
    {
      *pnode = new NodeOfList< T >(d, *pnode);
    }

    template< typename T >
    void pushBack(NodeOfList< T >** pnode, const T& data)
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
    T& getFront(NodeOfList< T >* node)
    {
      return node->data;
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

    template< typename T >
    void copy(NodeOfList< T >* first, NodeOfList< T >** result)
    {
      details::NodeOfList< T >* current = first;
      while (current)
      {
        details::pushBack(result, current->data);
        current = current->next;
      }
    }

    template< typename T >
    NodeOfList< T >* newCopy(NodeOfList< T >* other)
    {
      NodeOfList< T >* new_node = nullptr;
      try
      {
        copy(other, std::addressof(new_node));
      }
      catch (...)
      {
        clear(std::addressof(new_node));
        throw;
      }
      return new_node;
    }
  }
}
#endif

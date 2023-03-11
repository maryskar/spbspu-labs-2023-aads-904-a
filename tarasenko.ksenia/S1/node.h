#ifndef NODE_H
#define NODE_H
namespace tarasenko
{
  namespace details
  {
    template< typename T >
    struct NodeOfList
    {
      NodeOfList(T data, NodeOfList< T >* next) :
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
    void pushFront(NodeOfList< T >** plist, T d)
    {
      *plist = new NodeOfList< T >(d, *plist);
    }
  };
}
#endif

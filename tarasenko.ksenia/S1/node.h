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
    bool isEmpty(details::NodeOfList< T >* list)
    {
      return list == nullptr;
    }
  };
}
#endif

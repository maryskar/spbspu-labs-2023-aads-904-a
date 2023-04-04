#ifndef SPBSPU_LABS_2023_AADS_904_A_NODE_H
#define SPBSPU_LABS_2023_AADS_904_A_NODE_H
namespace dimkashelk
{
  namespace details
  {
    template < typename T >
    struct NodeOneWayList
    {
      T data;
      NodeOneWayList *next;
      explicit NodeOneWayList(const T &rhs):
        data(rhs),
        next(nullptr)
      {}
      NodeOneWayList(const T &rhs, NodeOneWayList< T > *next):
        data(rhs),
        next(next)
      {}
    };
    template < typename T >
    void freeList(NodeOneWayList< T > *start)
    {
      while (start)
      {
        auto node = start;
        start = start->next;
        delete node;
      }
    }
  }
}
#endif

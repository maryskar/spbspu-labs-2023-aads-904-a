#ifndef SPBSPU_LABS_2023_AADS_904_A_NODEFORWARDLIST_H
#define SPBSPU_LABS_2023_AADS_904_A_NODEFORWARDLIST_H
namespace dimkashelk
{
  namespace details
  {
    template < typename T >
    struct NodeForwardList
    {
      T data;
      NodeForwardList *next;
      NodeForwardList *prev;
      explicit NodeForwardList(const T &data):
        data(data),
        next(nullptr),
        prev(nullptr)
      {}
    };
  }
}
#endif

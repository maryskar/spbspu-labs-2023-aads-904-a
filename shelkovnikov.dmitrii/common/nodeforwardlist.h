#ifndef S2_NODEFORWARDLIST_H
#define S2_NODEFORWARDLIST_H
namespace dimkashelk
{
  namespace details
  {
    template <typename T>
    struct NodeForwardList
    {
      T data;
      NodeForwardList *next;
      NodeForwardList *prev;
      explicit NodeForwardList(const T &data) :
        data(data),
        next(nullptr),
        prev(nullptr)
      {}
    };
  }
}
#endif

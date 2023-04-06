#ifndef S2_NODEFORWARDLIST_H
#define S2_NODEFORWARDLIST_H
namespace dimkashelk
{
  namespace details
  {
    template <typename T>
    struct Node
    {
      T data;
      Node *next;
      Node *prev;
      explicit Node(const T &data) :
        data(data),
        next(nullptr),
        prev(nullptr)
      {}
    };
  }
}
#endif

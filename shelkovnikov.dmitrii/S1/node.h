#ifndef SPBSPU_LABS_2023_AADS_904_A_NODE_H
#define SPBSPU_LABS_2023_AADS_904_A_NODE_H
namespace details
{
  template< typename T >
  struct Node
  {
    T data;
    Node *next;
    explicit Node(T rhs):
      data(rhs),
      next(nullptr)
    {}
  };
}
#endif

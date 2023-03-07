#ifndef SPBSPU_LABS_2023_AADS_904_A_NODE_H
#define SPBSPU_LABS_2023_AADS_904_A_NODE_H
namespace details
{
  template< typename T >
  struct Node
  {
    T data_;
    Node *next_;
    explicit Node(T rhs):
      data_(rhs),
      next_(nullptr)
    {}
  };
}
#endif

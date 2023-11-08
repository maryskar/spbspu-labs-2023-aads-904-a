#ifndef TREE_H
#define TREE_H
#include <cstddef>
namespace aksenov
{
  template< class T >
  struct node_t
  {
    T data_;
    node_t *parent_;
    size_t height_;
    node_t *left_;
    node_t *right_;
    explicit node_t(const T &data, node_t *parent, size_t height = 1, node_t *left = nullptr, node_t *right = nullptr):
      data_(data),
      parent_(parent),
      height_(height),
      left_(left),
      right_(right)
    {}
  };
}
#endif



#ifndef TREE_H
#define TREE_H
namespace tarasenko
{
  namespace details
  {
    template< typename T, typename Compare >
    struct Tree
    {
      Tree():
        data_(),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr),
        color_('r'),
        compare_()
      {};

      Tree(const T& data, Tree< T, Compare >* left, Tree< T, Compare >* right, Tree< T, Compare >* parent):
        data_(data),
        left_(left),
        right_(right),
        parent_(parent),
        color_('r'),
        compare_()
      {};

      T data_;
      Tree< T, Compare >* left_;
      Tree< T, Compare >* right_;
      Tree< T, Compare >* parent_;
      char color_;
      Compare compare_;
    };
  }
}
#endif

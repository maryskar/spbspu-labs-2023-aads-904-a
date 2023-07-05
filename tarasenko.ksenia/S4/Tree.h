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
        compare_()
      {};

      T data_;
      Tree< T, Compare >* left_;
      Tree< T, Compare >* right_;
      Tree< T, Compare >* parent_;
      Compare compare_;
    };

    //insert
    //delete
    //leftRotation
    //rightRotation

  }
}
#endif

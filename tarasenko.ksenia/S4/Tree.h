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

    template< typename T, typename Compare >
    Tree< T, Compare >* insert(const T& data, Tree< T, Compare >* ptree)
    {
      auto comp = ptree->compare_;
      if (!ptree)
      {
        ptree = new Tree< T, Compare >;
        ptree->data_ = data;
      }
      else if (comp(data.first, ptree->data_.first))
      {
        Tree< T, Compare >* leftChild = insert(data, ptree->left_);
        ptree->left_ = leftChild;
        leftChild->parent_ = ptree;
      }
      else
      {
        Tree< T, Compare >* rightChild = insert(data, ptree->right_);
        ptree->right_ = rightChild;
        rightChild->parent_ = ptree;
      }
      return ptree;
    }

    template< typename T, typename Compare >
    void deleteTree(Tree< T, Compare >* ptree)
    {
      if (ptree)
      {
        deleteTree(ptree->left_);
        deleteTree(ptree->right_);
        delete ptree;
      }
    }
  }
}
#endif

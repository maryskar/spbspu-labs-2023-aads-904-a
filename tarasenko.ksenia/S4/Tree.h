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

    template< typename T, typename Compare >
    Tree< T, Compare >* find(const T& data, Tree< T, Compare >* ptree)
    {
      auto comp = ptree->compare_;
      if (!ptree || ptree->data_ == data)
      {
        return ptree;
      }
      if (comp(data, ptree->data_))
      {
        return find(data, ptree->left_);
      }
      return find(data, ptree->right_);
    }

    template< typename T, typename Compare >
    Tree< T, Compare >* findMin(Tree< T, Compare >* ptree)
    {
      if (!ptree)
      {
        return nullptr;
      }
      else if (!ptree->left_)
      {
        return ptree;
      }
      else
      {
        return findMin(ptree->left_);
      }
    }

    template< typename T, typename Compare >
    void remove(const T& data, Tree< T, Compare >* ptree)
    {
      auto toDelete = find(data, ptree);
      if (!toDelete)
      {
        return;
      }
      else if (toDelete->left_ && toDelete->right_)
      {
        auto replaceNode = findMin(toDelete->right_);
        toDelete->data_ = replaceNode->data_;
        remove(replaceNode->data_, replaceNode);
        return;
      }
      else
      {
        auto child = toDelete->left_ ? toDelete->left_ : toDelete->right_;
        if (toDelete->parent_)
        {
          if (toDelete->parent_->left_ == toDelete)
          {
            toDelete->parent_->left_ = child;
          }
          else
          {
            toDelete->parent_->right_ = child;
          }
          if (toDelete->left_ || toDelete->right_)
          {
            child->parent_ = toDelete->parent_;
          }
        }
        delete toDelete;
      }
    }
  }
}
#endif

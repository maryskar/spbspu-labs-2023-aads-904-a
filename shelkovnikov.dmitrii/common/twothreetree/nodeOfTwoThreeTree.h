#ifndef SPBSPU_LABS_2023_AADS_904_A_NODEOFTWOTHREETREE_H
#define SPBSPU_LABS_2023_AADS_904_A_NODEOFTWOTHREETREE_H
#include "nodeOfTwoThreeTreeOne.h"
#include "nodeOfTwoThreeTreeTwo.h"
namespace dimkashelk
{
  namespace details
  {
    template< typename Key, typename Value >
    class NodeOfTwoThreeTreeOne;
    template< typename Key, typename Value >
    class NodeOfTwoThreeTreeTwo;
    template< typename Key, typename Value >
    class NodeOfTwoThreeTree
    {
    using node_type = NodeOfTwoThreeTree< const Key, Value >;
    public:
      NodeOfTwoThreeTree(const Key &k, const Value &v):
        one_(new NodeOfTwoThreeTreeOne< Key, Value >(k, v)),
        two_(nullptr),
        size_(1)
      {}
      NodeOfTwoThreeTree(const Key &k1, const Value &v1, const Key &k2, const Value &v2):
        one_(nullptr),
        two_(new NodeOfTwoThreeTreeTwo< Key, Value >(k1, v1, k2, v2)),
        size_(2)
      {}
      ~NodeOfTwoThreeTree()
      {
        if (one_)
        {
          delete one_;
        }
        if (two_)
        {
          delete two_;
        }
      }
      unsigned getSize()
      {
        return size_;
      }
      void insert(const Key &k, const Value &v)
      {
        if (size_ == 2)
        {
          throw std::logic_error("No node with size more 2");
        }
        two_ = new NodeOfTwoThreeTreeTwo< Key, Value >(one_->data.first, one_->data.second, k, v);
        delete one_;
        size_ = 2;
      }
      void insertFront(const Key &k, const Value &v)
      {
        if (size_ == 2)
        {
          throw std::logic_error("No node with size more 2");
        }
        two_ = new NodeOfTwoThreeTreeTwo< Key, Value >(k, v, one_->data.first, one_->data.second);
        delete one_;
        size_ = 2;
      }
      NodeOfTwoThreeTree< Key, Value > *getFirstChild()
      {
        if (size_ == 1)
        {
          return one_->first;
        }
        else
        {
          return two_->first;
        }
      }
      void setFirstChild(node_type *node)
      {
        if (size_ == 1)
        {
          one_->first = node;
        }
        else
        {
          two_->first = node;
        }
      }
      NodeOfTwoThreeTree< Key, Value > *getSecondChild()
      {
        if (size_ == 1)
        {
          return one_->second;
        }
        else
        {
          return two_->second;
        }
      }
      void setSecondChild(node_type *node)
      {
        if (size_ == 1)
        {
          one_->second = node;
        }
        else
        {
          two_->second = node;
        }
      }
      NodeOfTwoThreeTree< Key, Value > *getThirdChild()
      {
        if (size_ == 1)
        {
          return nullptr;
        }
        else
        {
          return two_->third;
        }
      }
      void setThirdChild(node_type *node)
      {
        if (size_ == 1)
        {
          throw std::logic_error("No child!");
        }
        else
        {
          two_->third = node;
        }
      }
      std::pair< const Key, Value > &getData(unsigned ind_)
      {
        if (size_ == 1)
        {
          if (ind_ != 0)
          {
            throw std::out_of_range("No element");
          }
          return one_->data;
        }
        else
        {
          if (ind_ > 1)
          {
            throw std::out_of_range("No element");
          }
          return two_->data[ind_];
        }
      }
      NodeOfTwoThreeTree< Key, Value > *getParent()
      {
        if (size_ == 1)
        {
          return one_->parent;
        }
        else
        {
          return two_->parent;
        }
      }
      void setParent(node_type *node)
      {
        if (size_ == 1)
        {
          one_->parent = node;
        }
        else
        {
          two_->parent = node;
        }
      }
      NodeOfTwoThreeTree< Key, Value > *getLastChild()
      {
        if (size_ == 1)
        {
          return one_->getLastChildren();
        }
        else
        {
          return two_->getLastChildren();
        }
      }
      bool isList()
      {
        return getFirstChild() == nullptr && getSecondChild() == nullptr && getThirdChild() == nullptr;
      }
      NodeOfTwoThreeTreeOne< Key, Value > *getOneNode()
      {
        return one_;
      }
      NodeOfTwoThreeTreeTwo< Key, Value > *getTwoNode()
      {
        return two_;
      }
    private:
      NodeOfTwoThreeTreeOne< Key, Value > *one_;
      NodeOfTwoThreeTreeTwo< Key, Value > *two_;
      unsigned size_;
    };
  }
}
#endif

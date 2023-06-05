#ifndef SPBSPU_LABS_2023_AADS_904_A_NODEOFTWOTHREETREE_H
#define SPBSPU_LABS_2023_AADS_904_A_NODEOFTWOTHREETREE_H
#include <algorithm>
#include "math_functions.h"
namespace dimkashelk
{
  namespace details
  {
    template < typename Key, typename Value, typename Compare >
    struct NodeOfTwoThreeTree
    {
    public:
      using node_type = NodeOfTwoThreeTree< Key, Value, Compare >;
      std::pair< Key, Value > data[2];
      unsigned size;
      node_type *first;
      node_type *second;
      node_type *third;
      node_type *parent;
      NodeOfTwoThreeTree():
        data(),
        size(0),
        first(nullptr),
        second(nullptr),
        third(nullptr),
        parent(nullptr),
        compare_(Compare())
      {}
      NodeOfTwoThreeTree(const Key &k, const Value &v):
        data{{k, v}, {Key(), Value()}},
        size(1),
        first(nullptr),
        second(nullptr),
        third(nullptr),
        parent(nullptr),
        compare_(Compare())
      {}
      bool isList() const
      {
        return (first == nullptr) && (second == nullptr) && (third == nullptr);
      }
      void insert(const Key &k, const Value &v)
      {
        data[size] = {k, v};
        size++;
        sort();
      }
      node_type *getLastChildren()
      {
        return (third)? third: (second)? second: first;
      }
      bool contains(const Key &k)
      {
        for (unsigned int i = 0; i < size; ++i)
        {
          if (details::isEqual< Key, Compare >(data[i].first, k))
          {
            return true;
          }
        }
        return false;
      }
      void removeFromNode(Key k)
      {
        if (size >= 1 && details::isEqual< Key, Compare >(data[0].first, k))
        {
          data[0] = data[1];
          size--;
        }
        else if (size == 2 && details::isEqual< Key, Compare >(data[1].first, k))
        {
          size--;
        }
      }
    private:
      Compare compare_;
      void sort()
      {
        if (!compare_(data[0].first, data[1].first))
        {
          std::swap(data[0], data[1]);
        }
      }
    };
  }
}
#endif

#ifndef SPBSPU_LABS_2023_AADS_904_A_NODETOINSERT_H
#define SPBSPU_LABS_2023_AADS_904_A_NODETOINSERT_H
#include <algorithm>
#include "math_functions.h"
#include "nodeOfTwoThreeTree.h"
namespace dimkashelk
{
  namespace details
  {
    template < typename Key, typename Value, typename Compare >
    struct NodeToInsert
    {
    public:
      using node_type = NodeOfTwoThreeTree< Key, Value, Compare >;
      std::pair< Key, Value > data[3];
      unsigned size;
      node_type *first;
      node_type *second;
      node_type *third;
      node_type *fourth;
      node_type *parent;
      NodeToInsert(NodeOfTwoThreeTree< Key, Value, Compare > *node):
        data{node->data[0], node->data[1]},
        size(node->size),
        first(node->first),
        second(node->second),
        third(node->third),
        fourth(nullptr),
        parent(node->parent),
        compare_(Compare())
      {}
      void insert(const Key &k, const Value &v)
      {
        data[size] = {k, v};
        size++;
        sort();
      }
      void becomeNode2(const Key &k, const Value &v, node_type *first_, node_type *second_)
      {
        data[0] = {k, v};
        first = first_;
        second = second_;
        third = nullptr;
        fourth = nullptr;
        parent = nullptr;
        size = 1;
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
          data[1] = data[2];
          size--;
        }
        else if (size == 2 && details::isEqual< Key, Compare >(data[1].first, k))
        {
          data[1] = data[2];
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
        if (size == 3)
        {
          if (!compare_(data[0].first, data[2].first))
          {
            std::swap(data[0], data[2]);
          }
          if (!compare_(data[1].first, data[2].first))
          {
            std::swap(data[1], data[2]);
          }
        }
      }

    };
  }
}
#endif

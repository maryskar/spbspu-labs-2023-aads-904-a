#ifndef SPBSPU_LABS_2023_AADS_904_A_NODEOFTWOTHREETREEONE_H
#define SPBSPU_LABS_2023_AADS_904_A_NODEOFTWOTHREETREEONE_H
#include "nodeOfTwoThreeTree.h"
namespace dimkashelk
{
  namespace details
  {
    template < typename Key, typename Value >
    struct NodeOfTwoThreeTree;
    template < typename Key, typename Value >
    struct NodeOfTwoThreeTreeOne
    {
      using node_type = NodeOfTwoThreeTree< Key, Value >;
      std::pair< const Key, Value > data;
      unsigned size;
      node_type *first;
      node_type *second;
      node_type *parent;
      NodeOfTwoThreeTreeOne(const Key &k, const Value &v):
        data(k, v),
        size(1),
        first(nullptr),
        second(nullptr),
        parent(nullptr)
      {}
      bool isList() const
      {
        return (first == nullptr) && (second == nullptr);
      }
      node_type *getLastChildren()
      {
        return (second)? second: first;
      }
    };
  }
}
#endif

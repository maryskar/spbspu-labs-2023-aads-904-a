#ifndef SPBSPU_LABS_2023_AADS_904_A_NODEOFTWOTHREETREETWO_H
#define SPBSPU_LABS_2023_AADS_904_A_NODEOFTWOTHREETREETWO_H
#include "nodeOfTwoThreeTree.h"
namespace dimkashelk
{
  namespace details
  {
    template < typename Key, typename Value >
    struct NodeOfTwoThreeTree;
    template < typename Key, typename Value >
    struct NodeOfTwoThreeTreeTwo
    {
      using node_type = NodeOfTwoThreeTree< Key, Value >;
      std::pair< const Key, Value > data[2];
      unsigned size;
      node_type *first;
      node_type *second;
      node_type *third;
      node_type *parent;
      NodeOfTwoThreeTreeTwo(const Key &k1, const Value &v1, const Key &k2, const Value &v2):
        data{{k1, v1}, {k2, v2}},
        size(2),
        first(nullptr),
        second(nullptr),
        third(nullptr),
        parent(nullptr)
      {}
      bool isList() const
      {
        return (first == nullptr) && (second == nullptr) && (third == nullptr);
      }
      node_type *getLastChildren()
      {
        return (third)? third: (second)? second: first;
      }
    };
  }
}
#endif

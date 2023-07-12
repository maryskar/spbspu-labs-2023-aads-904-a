#ifndef SPBSPU_LABS_2023_AADS_904_A_NODETOINSERT_H
#define SPBSPU_LABS_2023_AADS_904_A_NODETOINSERT_H
#include <algorithm>
#include "math_functions.h"
#include "nodeOfTwoThreeTree.h"
namespace dimkashelk
{
  namespace details
  {
    template < typename Key, typename Value >
    struct NodeToInsert
    {
    public:
      using node_type = NodeOfTwoThreeTree< const Key, Value >;
      std::pair< const Key, Value > data[3];
      unsigned size;
      node_type *first;
      node_type *second;
      node_type *third;
      node_type *fourth;
      node_type *parent;
      NodeToInsert(node_type *node, const Key &k, const Value &v):
        data{node->getData(0), node->getData(1), k, v},
        size(node->getSize()),
        first(node->getFirstChild()),
        second(node->getSecondChild()),
        third(node->getThirdChild()),
        fourth(nullptr),
        parent(node->getParent())
      {}
    };
  }
}
#endif

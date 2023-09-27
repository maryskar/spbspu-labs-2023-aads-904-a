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
      using node_type = NodeOfTwoThreeTree< Key, Value >;
      using data_type = std::pair< const Key, Value >;
      data_type data[3];
      unsigned size;
      node_type *first;
      node_type *second;
      node_type *third;
      node_type *fourth;
      node_type *parent;
      NodeToInsert(data_type &p1, data_type &p2, data_type &p3, node_type *node):
        data{p1, p2, p3},
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

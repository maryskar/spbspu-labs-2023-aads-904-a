#ifndef SPBSPU_LABS_2023_AADS_904_A_DATA_H
#define SPBSPU_LABS_2023_AADS_904_A_DATA_H
#include "nodeOfTwoThreeTreeOne.h"
#include "nodeOfTwoThreeTreeTwo.h"
namespace dimkashelk
{
  namespace details
  {
    template< typename Key, typename Value >
    union Data
    {
      using node_one_type = NodeOfTwoThreeTreeOne< Key, Value >;
      using node_two_type = NodeOfTwoThreeTreeTwo< Key, Value >;
      Data(node_one_type *node):
        one_(node)
      {}
      Data(node_two_type *node):
        two_(node)
      {}
      node_one_type *one_;
      node_two_type *two_;
    };
  }
}
#endif

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
      NodeOfTwoThreeTreeOne< Key, Value > *one_;
      NodeOfTwoThreeTreeTwo< Key, Value > *two_;
    };
  }
}
#endif

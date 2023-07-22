#include "structsForTraverse.h"

namespace mashkin
{
  void QueueForTraverse::operator()(const std::pair< const int, std::string >& key_value)
  {
    res_.enqueue(key_value.second);
  }
}

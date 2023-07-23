#include "structsForTraverse.h"

namespace mashkin
{
  void QueueForTraverse::operator()(const std::pair< const int, std::string >& key_value)
  {
    summ_ += key_value.first;
    res_.enqueue(key_value.second);
  }

  void StackForTraverse::operator()(const std::pair< const int, std::string >& key_value)
  {
    summ_ += key_value.first;
    res_.push(key_value.second);
  }
}

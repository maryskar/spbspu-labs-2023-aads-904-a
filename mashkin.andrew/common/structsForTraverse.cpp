#include "structsForTraverse.h"
#include <limits>
#include <stdexcept>

namespace mashkin
{
  constexpr auto maxInt = std::numeric_limits< int >::max();
  constexpr auto minInt = std::numeric_limits< int >::min();
  void getSumm(int& summ_, const std::pair< const int, std::string >& key_value)
  {
    if (summ_ >= 0)
    {
      if (maxInt - summ_ >= key_value.first)
      {
        summ_ += key_value.first;
      }
      else
      {
        throw std::overflow_error("Overflow of int");
      }
    }
    else
    {
      if (minInt - summ_ <= key_value.first)
      {
        summ_ += key_value.first;
      }
      else
      {
        throw std::underflow_error("Underflow of int");
      }
    }
  }

  void QueueForTraverse::operator()(const std::pair< const int, std::string >& key_value)
  {
    getSumm(summ_, key_value);
    res_.enqueue(key_value.second);
  }

  void StackForTraverse::operator()(const std::pair< const int, std::string >& key_value)
  {
    getSumm(summ_, key_value);
    res_.push(key_value.second);
  }
}

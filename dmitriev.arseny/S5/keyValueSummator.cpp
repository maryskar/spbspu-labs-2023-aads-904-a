#include "keyValueSummator.h"
#include <limits>
#include <stdexcept>

int getSumm(int sum, int key)
{
  if (sum >= 0)
  {
    if (std::numeric_limits< int >::max() - sum >= key)
    {
      sum += key;
    }
    else
    {
      throw std::overflow_error("overflow");
    }
  }
  else
  {
    if (std::numeric_limits< int >::min() - sum <= key)
    {
      sum += key;
    }
    else
    {
      throw std::underflow_error("underflow");
    }
  }

  return sum;
}


void dmitriev::KeyValueSummator::operator()(const std::pair< const int, std::string >& val)
{
  resultNumber = getSumm(resultNumber, val.first);
  resultStr += " ";
  resultStr += val.second;
}

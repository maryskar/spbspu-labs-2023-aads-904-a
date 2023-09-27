#include "keyValueSummator.h"
#include <limits>
#include <stdexcept>

long long getSumm(int sum, int key)
{
  if (sum >= 0)
  {
    if (std::numeric_limits< int >::max() - sum >= key)
    {
      sum += key;
    }
    else
    {
      throw std::overflow_error("Overflow of int");
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
      throw std::underflow_error("Underflow of int");
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

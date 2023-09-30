#include "keysummator.hpp"

#include <utility>
#include <string>

#include <arithmetic.hpp>

void hrushchev::KeySummator::operator()(const std::pair< const long long, std::string >& key_value)
{
  long long key = key_value.first;
  if ((result_ >= 0) && (key > 0))
  {
    result_ = hrushchev::sum(result_, key);
  }
  else if ((result_ < 0) && (key > 0))
  {
    result_ = hrushchev::sum(key, result_);
  }
  else
  {
    result_ = hrushchev::subtract(result_, -1ll * key);
  }
}


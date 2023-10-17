#ifndef KEYSUMMATOR_HPP
#define KEYSUMMATOR_HPP

#include <utility>
#include <string>

namespace hrushchev
{
  struct KeySummator
  {
    void operator()(const std::pair< const long long, std::string >& key_value);
    long long result_ = 0;
  };
}

#endif

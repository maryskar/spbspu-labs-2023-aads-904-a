#ifndef STRINGCREATOR_HPP
#define STRINGCREATOR_HPP

#include <utility>
#include <string>

namespace hrushchev
{
  struct StringCreator
  {
    void operator()(const std::pair< const long long, std::string >& key_value);
    std::string result_ = "";
  };
}

#endif

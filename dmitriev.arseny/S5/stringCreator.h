#ifndef STRINGCREATOR_H
#define STRINGCREATOR_H

#include <string>

namespace dmitriev
{
  struct StringCreator
  {
    void operator()(const std::pair< const long long, std::string >& val);

    std::string result = "";
  };
}

#endif

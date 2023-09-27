#ifndef STRINGCREATOR_H
#define STRINGCREATOR_H

#include <string>

namespace dmitriev
{
  struct StringCreator
  {
    void operator()(const std::pair< const int, std::string >& val);

    int resultNumber = 0;
    std::string resultStr = "";
  };
}

#endif

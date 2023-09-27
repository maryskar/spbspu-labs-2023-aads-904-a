#ifndef STRINGCREATOR_H
#define STRINGCREATOR_H

#include <string>

namespace dmitriev
{
  struct StringCreator
  {
    void operator()(std::pair< int, std::string >& val);

    std::string result = "";
  };
}

#endif

#include "getDicts.h"
#include <stdexcept>
#include <string>
#include "Commands.h"
#include "Dictionary.h"

namespace chulkov {
  Dictionary< int, std::string > getDict(const FrdList< std::string >& in)
  {
    Dictionary< int, std::string > returnable;
    int key = 0;
    std::string string;
    for (ForwardConstIter< std::string > i = (++in.cbegin()); i != in.cend(); ++i) {
      if (std::isdigit(i->front())) {
        key = std::stoi(*i);
        continue;
      }
      string = *i;
      returnable.push(key, string);
    }
    return returnable;
  }

}

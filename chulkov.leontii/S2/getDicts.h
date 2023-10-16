#ifndef GETDICTS_H
#define GETDICTS_H
#include <iosfwd>
#include <string>
#include "commands.h"

namespace chulkov {
  Dicts getDicts(std::istream&);
  ForwardList< std::string > getWords(std::istream&, char);
}

#endif

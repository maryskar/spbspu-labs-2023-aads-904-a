#ifndef GETDICTS_H
#define GETDICTS_H
#include <iosfwd>
#include <string>
#include "Commands.h"
#include "ForwardList.h"

namespace chulkov {
  Dicts getDicts(std::istream&);
  FrdList< std::string > getWords(std::istream&, char);
}

#endif

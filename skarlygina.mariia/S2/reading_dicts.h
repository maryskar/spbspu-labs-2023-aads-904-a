#ifndef READING_DICTS_H
#define READING_DICTS_H
#include <string>
#include <iosfwd>
#include "forwardlist.h"
#include "commands.h"

namespace skarlygina
{
  Dictis getDictis(std::istream&);
  ForwardList< std::string > getWords(std::istream&, char);
}

#endif
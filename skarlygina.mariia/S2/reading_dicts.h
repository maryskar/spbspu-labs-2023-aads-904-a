#ifndef READING_DICTS_H
#define READING_DICTS_H
#include <string>
#include <iosfwd>
#include "forwardlist.h"
#include "commands.h"

namespace skarlygina
{
  void readCommand(Dictis data, std::string& lhs, std::string& rhs, std::string& command, std::string& name);
  Dictionary< std::string, Dictionary< int, std::string > > getDictis(std::istream&);
  ForwardList< std::string > getWords(std::istream&, char);
}

#endif
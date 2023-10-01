#ifndef INPUTCOMMANDS_H
#define INPUTCOMMANDS_H

#include "dictionary.h"

namespace potapova
{
  template< bool (*compareFunc)(const long long&, const long long&), bool (*compareDict)(const std::string& first, const std::string& second) >
  void runCommand(std::string& command, Dictionary< std::string, Dictionary< long long, std::string, compareFunc >, compareDict > variables);
}

#endif

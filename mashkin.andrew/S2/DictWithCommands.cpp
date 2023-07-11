#include "DictWithCommands.h"
#include <string>
#include <map>
#include "commands.h"
#include "dictionary.h"

namespace mashkin
{
  void createDictWithCommnads(Dictionary< std::string, void (*)(std::istream&, dictionaries&) >& dict)
  {
    std::map< std::string, void (*)(std::istream&, dictionaries&) > dicty;
    dict["print"] = print;
  }
}

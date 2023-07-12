#include "DictWithCommands.h"
#include <string>
#include <map>
#include "commands.h"
#include "dictionary.h"

namespace mashkin
{
  void createDictWithCommnads(Dictionary< std::string, void (*)(std::istream&, dictionaries&) >& dict)
  {
    dict["print"] = print;
    dict["complement"] = complement;
    dict["intersect"] = intersect;
  }
}

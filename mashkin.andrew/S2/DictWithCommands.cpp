#include "DictWithCommands.h"
#include <string>
#include "commands.h"
#include "dictionary.h"

namespace mashkin
{
  Dictionary< std::string, void (*)(std::istream&, dictionaries&) > createDictWithCommnads()
  {
    Dictionary< std::string, void (*)(std::istream&, dictionaries&) > dict;
    dict["print"] = print;
    dict["complement"] = complement;
    dict["intersect"] = intersect;
    dict["union"] = unionDicts;
    return dict;
  }
}

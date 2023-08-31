#include "commandSet.h"
#include "Dictionary.h"
#include "Commands.h"
namespace timofeev
{
  //no overload oper[]
  void cmdSet(Dictionary< std::string, void (*)(std::istream&, dictOfDicts& dict, std::ostream&) >& command)
  {
    command["print"] = Print;
    command["complement"] = Complement;
    command["intersect"] = Intersect;
    command["union"] = Union;
  }
}
#include "commandSet.h"
#include "Dictionary.h"
#include "Commands.h"
namespace timofeev
{
  comDict cmdSet(comDict& command)
  {
    command["complement"] = Complement;
    command["intersect"] = Intersect;
    command["union"] = Union;
    return command;
  }
}
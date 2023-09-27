#include "commandSet.h"
#include "Dictionary.h"
#include "Commands.h"
timofeev::comDict timofeev::cmdSet(comDict& command)
{
  command["complement"] = Complement;
  command["intersect"] = Intersect;
  command["union"] = Union;
  return command;
}

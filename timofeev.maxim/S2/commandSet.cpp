#include "commandSet.h"
#include "Dictionary.h"
#include "Commands.h"
timofeev::comDict timofeev::cmdSet()
{
  timofeev::comDict command;
  command["complement"] = doComplement;
  command["intersect"] = doIntersect;
  command["union"] = doUnion;
  return command;
}

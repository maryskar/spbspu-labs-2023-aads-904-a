#include "commands.h"
void aksenov::createCommandDict(aksenov::commandMap &commands)
{
  commands["intersect"] = intersect< dict >;
  commands["union"] = unite< dict >;
  commands["complement"] = doComplement< dict >;
}

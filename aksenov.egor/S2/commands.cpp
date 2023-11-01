#include "commands.h"
namespace aksenov
{
  commandMap createCommandDict()
  {
    commandMap commands;
    commands["intersect"] = intersect< dict >;
    commands["union"] = unite< dict >;
    commands["complement"] = doComplement< dict >;
    return commands;
  }
}

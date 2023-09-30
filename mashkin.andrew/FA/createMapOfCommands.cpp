#include "createMapOfCommands.h"
#include <iostream>
#include "AVL/AVL.h"
#include "commands.h"

namespace mashkin
{
  MapOfCommands createMapOfCommands()
  {
    MapOfCommands mapOfCommands;
    mapOfCommands["add"] = addExpr;
    mapOfCommands["simplify"] = simplifyExpr;
    mapOfCommands["parameters"] = getParameters;
    mapOfCommands["set"] = setNewExpr;
    mapOfCommands["show"] = showExpr;
    return mapOfCommands;
  }
}

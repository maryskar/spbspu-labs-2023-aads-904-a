#include "commandSet.h"
namespace timofeev
{
  void cmdSet()
  {
    command["print"] = Print;
    command["complement"] = Complement;
    command["intersect"] = Intersect;
    command["union"] = Union;
  }
}
#include "dictionary.h"
namespace timofeev
{
  void dictionary()
  {
    command["print"] = Print;
    command["complement"] = Complement;
    command["intersect"] = Intersect;
    command["union"] = Union;
  }
}
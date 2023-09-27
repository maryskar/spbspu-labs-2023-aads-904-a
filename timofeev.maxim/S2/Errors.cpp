#include "Errors.h"
namespace errors
{
  void printInvalid(std::ostream& out)
  {
    out << "<INVALID COMMAND>" << '\n';
  }
  void printError(std::ostream& out)
  {
    out << "<ERROR>" << '\n';
  }
}

#include "Errors.h"
namespace errors
{
  void printInvalid(std::ostream& out)
  {
    out << "<INVALID COMMAND>" << '\n';
  }
  void printEmpty(std::ostream& out)
  {
    out << "<EMPTY>" << '\n';
  }
  void printError(std::ostream& out)
  {
    out << "<ERROR>" << '\n';
  }
}

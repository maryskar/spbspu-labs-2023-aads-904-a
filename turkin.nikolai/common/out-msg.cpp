#include <out-msg.hpp>

void turkin::outInvalidCMD(std::ostream & out)
{
  out << "<INVALID COMMAND>\n";
}

void turkin::outEmptyCMD(std::ostream & out)
{
  out << "<EMPTY>\n";
}

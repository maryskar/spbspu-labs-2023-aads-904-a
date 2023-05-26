#include "printer.hpp"
#include <iostream>

namespace chemodurov
{
  Printer::Printer(std::ostream & out):
   out_(out),
   was_printed_(false)
  {}

  void Printer::operator()(const std::pair< int, std::string > & pair)
  {
    if (was_printed_)
    {
      out_ << ' ';
    }
    out_ << pair.second;
    if (!was_printed_)
    {
      was_printed_ = true;
    }
  }
}

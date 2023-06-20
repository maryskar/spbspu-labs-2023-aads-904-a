#ifndef CMD_WORK_HPP
#define CMD_WORK_HPP

#include <cstddef>
#include <string>
#include <strstream>
#include "dictionary.hpp"

//print
//complement
//intersect
//union

namespace turkin
{
  using dict = Dictionary< size_t, std::string, int >;
  void print(const dict & rhs, const std::ostrstream & out);
  dict complement(const dict & one, const dict & two);
  dict intersect(const dict & one, const dict & two);
  dict toghether(const dict & one, const dict & two);
}

#endif

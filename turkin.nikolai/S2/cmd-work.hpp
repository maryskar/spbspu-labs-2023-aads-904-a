#ifndef CMD_WORK_HPP
#define CMD_WORK_HPP

#include <cstddef>
#include <string>
#include <fstream>
#include <functional>
#include "dictionary.hpp"

namespace turkin
{
  using dict = Dictionary< size_t, std::string, std::less< std::size_t > >;
  void print(const std::pair< std::string, dict > & rhs, std::ostream & out);
  dict to_complement(const dict & one, const dict & two);
  dict to_intersect(const dict & one, const dict & two);
  dict to_union(const dict & one, const dict & two);
}

#endif

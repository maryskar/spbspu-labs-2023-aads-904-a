#ifndef S5_CREATE_ARGS_MAP_HPP
#define S5_CREATE_ARGS_MAP_HPP
#include <map.hpp>
#include "printer.hpp"

namespace chemodurov
{
  using ptr_t = Printer (Map< int, std::string >::*)(Printer pr);
  using args_dic_t = Map< std::string, ptr_t >;
  args_dic_t createArgsMap();
}

#endif

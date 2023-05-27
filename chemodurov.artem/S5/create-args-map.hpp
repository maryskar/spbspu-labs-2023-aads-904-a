#ifndef S5_CREATE_ARGS_MAP_HPP
#define S5_CREATE_ARGS_MAP_HPP
#include <map.hpp>
#include "printer.hpp"

namespace chemodurov
{
  template< typename F >
  using ptr_t = F (Map< int, std::string >::*)(F f);
  using args_dic_t = Map< std::string, ptr_t< Printer > >;
  args_dic_t createArgsMap();
}

#endif

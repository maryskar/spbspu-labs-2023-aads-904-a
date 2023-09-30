#include "create-args-map.hpp"

chemodurov::args_dic_t chemodurov::createArgsMap()
{
  args_dic_t map;
  map.insert({"ascending", &Map< long, std::string >::traverse_lnr});
  map.insert({"descending", &Map< long, std::string >::traverse_rnl});
  map.insert({"breadth", &Map< long, std::string >::traverse_breadth});
  return map;
}

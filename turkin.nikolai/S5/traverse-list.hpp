#ifndef TRAVERSE_LIST_HPP
#define TRAVERSE_LIST_HPP

#include <string>
#include <avl-tree/avl-tree.hpp>

namespace turkin
{
  template< typename F >
  using trvs_t = F (AVLtree< int, std::string, std::less< > >::*)(F f);
  template< typename F >
  using trvs_m = AVLtree< std::string, trvs_t< F >, std::less< > >;
  
  template< typename F >
  decltype(auto) make_trvs()
  {
    trvs_m< F > result;
    result.insert("ascending", &AVLtree< int, std::string, std::less< > >::traverse_lnr);
    result.insert("descending", &AVLtree< int, std::string, std::less< > >::traverse_rnl);
    result.insert("breadth", &AVLtree< int, std::string, std::less< > >::traverse_breadth);
    return result;
  }
}

#endif

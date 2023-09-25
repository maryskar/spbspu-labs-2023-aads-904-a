#ifndef CREATETREEWITHREAVERSES_H
#define CREATETREEWITHTRAVERSES_H
#include <string>
#include <avl/AVL.h>
namespace fesenko
{
  template< typename F >
  using cmd_t = F (AVL< long long, std::string, std::less< > >::*)(F f);
  template< typename F >
  using trvrs = AVL< std::string, cmd_t< F >, std::less< > >;
  template< typename F >
  decltype(auto) createTreeWithTraverses()
  {
    trvrs< F > result;
    result.insert({"ascending", &AVL< long long, std::string, std::less< > >::traverse_lnr});
    result.insert({"descending", &AVL< long long, std::string, std::less< > >::traverse_rnl});
    result.insert({"breadth", &AVL< long long, std::string, std::less< > >::traverse_breadth});
    return result;
  }
}
#endif

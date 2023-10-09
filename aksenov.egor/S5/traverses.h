#ifndef TRAVERSES_H
#define TRAVERSES_H
#include <string>
#include <AVL/AVL.h>
namespace aksenov
{
  template< typename F >
  using traverse = F (AVL< long long, std::string, std::less< > >::*)(F f);
  template< typename F >
  using traverseMap = AVL< std::string, traverse< F >, std::less< > >;
  template< typename F >
  decltype(auto) makeTraverse()
  {
    traverseMap< F > res;
    res.insert("ascending", &AVL< long long, std::string, std::less< > >::traverse_lnr);
    res.insert("descending", &AVL< long long, std::string, std::less< > >::traverse_rnl);
    res.insert("breadth", &AVL< long long, std::string, std::less< > >::traverse_breadth);
    return res;
  }
}
#endif
#ifndef TRAVERSES_H
#define TRAVERSES_H
#include <string>
#include <AVL/AVL.h>
namespace aksenov
{
  template< typename F >
  using traverse = F (AVL< long long, std::string, std::less< > >::*)(F f) const;
  template< typename F >
  using traverseMap = AVL< std::string, traverse< F >, std::less< > >;
  template< typename F >
  auto makeTraverse() -> traverseMap< F >
  {
    traverseMap< F > res;
    res["ascending"] = &AVL< long long, std::string, std::less< > >::template traverse_lnr;
    res["descending"] = &AVL< long long, std::string, std::less< > >::template traverse_rnl;
    res["breadth"] = &AVL< long long, std::string, std::less< > >::template traverse_breadth;
    return res;
  }
}
#endif
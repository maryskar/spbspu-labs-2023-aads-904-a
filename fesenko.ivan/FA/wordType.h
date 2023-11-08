#ifndef WORDTYPE_H
#define WORDTYPE_H
#include "dictionary/forward-list/forwardList.h"
namespace fesenko
{
  template< typename T >
  struct WordType
  {
    std::string word = "";
    T data;
    ForwardList< std::pair< std::string, T > > collision_list;
  };
}
#endif

#ifndef WORDTYPE_H
#define WORDTYPE_H
#include "dictionary/forward-list/forwardList.h"
namespace fesenko
{
  struct WordType
  {
    std::string word = "";
    ForwardList< size_t > numbers;
  };
}
#endif

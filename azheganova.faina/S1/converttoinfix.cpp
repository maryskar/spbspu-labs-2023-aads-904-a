#include "converttoinfix.h"

azheganova::Queue< std::string > convertToInfix(const std::string & string)
{
  azheganova::Queue< std::string > infix;
  size_t begin = 0;
  int end = string.find(' ');
  while (end >= 0)
  {
    infix.push(string.substr(begin, end - begin));
    begin = end + 1;
    end = string.find(' ', begin);
  }
  infix.push(string.substr(begin, end - begin));
  return infix;
}

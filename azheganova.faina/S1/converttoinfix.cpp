#include "converttoinfix.h"

azheganova::Queue< std::string > azheganova::convertToInfix(const std::string & string)
{
  Queue< std::string > infix;
  size_t begin = 0;
  size_t end = string.find(' ');
  while (end + 1 > 0)
  {
    infix.push(string.substr(begin, end - begin));
    begin = end + 1;
    end = string.find(' ', begin);
  }
  infix.push(string.substr(begin, end - begin));
  return infix;
}

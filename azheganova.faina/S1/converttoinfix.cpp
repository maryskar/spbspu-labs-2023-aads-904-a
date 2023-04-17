#include "converttoinfix.h"

Queue< std::string > convertToInfix(const std::string & string)
{
  Queue< std::string > infix;
  int begin = 0;
  int end = string.find(' ');
  while (end > -1)
  {
    infix.push(string.substr(begin, end - begin));
    begin = end + 1;
    end = string.find(' ', begin);
  }
  infix.push(string.substr(begin, end - begin));
  return infix;
}

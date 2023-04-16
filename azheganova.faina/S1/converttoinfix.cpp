#include "converttoinfix.h"

Queue< std::string > convertToInfix(const std::string & string)
{
  Queue< std::string > infix;
  int begin = 0;
  int end = string.find(' ');
  int count = 0;
  while (end > -1)
  {
    count = end - begin;
    infix.push(string.substr(begin, end - begin));
    begin = end + 1;
    end = string.find(' ', begin);
  }
  count = end - begin;
  infix.push(string.substr(begin, count));
  return infix;
}

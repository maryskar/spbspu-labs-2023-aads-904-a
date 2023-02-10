#include "parser.h"
#include <stdexcept>
dimkashelk::Parser::Parser(std::string str):
  begin(str.begin()),
  end(str.end())
{
  while (begin != end && *begin == ' ')
  {
    begin++;
  }
  if (begin == end)
  {
    throw std::logic_error("String must contains elements");
  }
}
std::string dimkashelk::Parser::operator()()
{
  std::string res = "";
  while (begin != end && *begin != ' ')
  {
    res.push_back(*begin);
  }
  return res;
}
bool dimkashelk::Parser::hasNext()
{
  while (begin != end && *begin == ' ')
  {
    begin++;
  }
  return begin != end;
}

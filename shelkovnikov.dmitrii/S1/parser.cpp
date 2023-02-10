#include "parser.h"
#include <stdexcept>
dimkashelk::Parser::Parser(std::string str):
  data_(str.data()),
  i_(0)
{
  while (data_[i_] == ' ')
  {
    i_++;
  }
  if (data_[i_] == '\0')
  {
    throw std::logic_error("String must contains elements");
  }
}
std::string dimkashelk::Parser::operator()()
{
  std::string res = "";
  while (data_[i_] && data_[i_] != ' ')
  {
    res.push_back(data_[i_]);
    i_++;
  }
  return res;
}
bool dimkashelk::Parser::hasNext()
{
  while (data_[i_] && data_[i_] == ' ')
  {
    i_++;
  }
  return data_[i_] != '\0';
}

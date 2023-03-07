#include "parser.h"
#include <stdexcept>
dimkashelk::Parser::Parser(std::string str):
  data_(str),
  i_(0)
{
  while (std::isspace(data_[i_]))
  {
    i_++;
  }
  if (!data_[i_])
  {
    throw std::logic_error("String must contains elements");
  }
}
std::string dimkashelk::Parser::operator()()
{
  std::string res;
  while (data_[i_] && !std::isspace(data_[i_]))
  {
    res.push_back(data_[i_]);
    i_++;
  }
  return res;
}
bool dimkashelk::Parser::hasNext()
{
  while (data_[i_] && std::isspace(data_[i_]))
  {
    i_++;
  }
  return data_[i_];
}

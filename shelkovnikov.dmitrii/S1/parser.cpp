#include "parser.h"
#include <stdexcept>
dimkashelk::Parser::Parser(std::string str):
  data_(std::move(str)),
  i_(0)
{
  size_t firstNotSpace = data_.find_first_not_of(" \n");
  if (firstNotSpace == std::string::npos)
  {
    throw std::logic_error("String must contains elements");
  }
  data_ = data_.substr(firstNotSpace);
}
std::string dimkashelk::Parser::operator()()
{
  std::string res;
  size_t start = data_.find_first_not_of(" \n");
  if (start == std::string::npos)
  {
    return res;
  }
  data_ = data_.substr(start);
  size_t end = data_.find_first_of(" \n");
  if (end == std::string::npos)
  {
    res = data_;
    data_ = "";
    return res;
  }
  res = data_.substr(0, end);
  data_ = data_.substr(end);
  return res;
}
bool dimkashelk::Parser::hasNext() const
{
  return data_.find_first_not_of(" \n") != std::string::npos;
}

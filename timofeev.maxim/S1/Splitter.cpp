#include "Splitter.h"
#include <cstddef>
#include <stdexcept>

timofeev::Splitter::Splitter(const std::string& str):
        str_(str),
        split_("")
{}
bool timofeev::Splitter::empty() const
{
  return str_.empty();
}
const std::string& timofeev::Splitter::getSplit()
{
  if (str_.empty())
  {
    throw std::invalid_argument("Empty string");
  }
  size_t space = str_.find_first_of(' ');
  if (space == str_.npos)
  {
    throw std::invalid_argument("invalid_argument dsf");
  }
  std::string String = str_.substr(0, space);
  if (space == str_.size() - 1)
  {
    str_.clear();
  }
  else
  {
    str_ = str_.substr(space + 1);
  }
  return String;
}

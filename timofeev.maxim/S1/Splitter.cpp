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
    throw std::runtime_error("Read error");
  }
  size_t space = str_.find_first_of(' ');
  if (space == str_.npos)
  {
    split_ = str_;
    str_.clear();
  }
  else
  {
    split_ = str_.substr(0, space);
    str_ = str_.substr(space + 1);
  }
  return split_;
}

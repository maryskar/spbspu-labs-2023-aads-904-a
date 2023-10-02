#include "StringSplitter.hpp"

#include <cstddef>
#include <stdexcept>

odintsov::StringSplitter::StringSplitter(const std::string& str):
  str_(str)
{}

odintsov::StringSplitter& odintsov::StringSplitter::operator>>(std::string& ostr)
{
  if (str_.empty()) {
    throw std::runtime_error("Read error");
  }
  size_t spaceIndex = str_.find_first_of(' ');

  ostr = str_.substr(0, spaceIndex);
  if (spaceIndex == str_.npos) {
    str_.clear();
  } else {
    str_ = str_.substr(spaceIndex + 1);
  }
  return *this;
}

bool odintsov::StringSplitter::empty() const
{
  return str_.empty();
}

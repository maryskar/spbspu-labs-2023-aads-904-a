#include "Splitter.h"

timofeev::Splitter::Splitter(const std::string& str):
        str_(str),
        split_("")
{}
bool timofeev::Splitter::empty() const
{
  return str_.empty();
}
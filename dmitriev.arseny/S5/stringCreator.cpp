#include "stringCreator.h"

void dmitriev::StringCreator::operator()(std::pair< int, std::string >& val)
{
  if (!result.empty())
  {
    result += " ";
  }

  result += val.second;
}

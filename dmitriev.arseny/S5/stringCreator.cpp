#include "stringCreator.h"

void dmitriev::StringCreator::operator()(const std::pair< const long long, std::string >& val)
{
  if (!result.empty())
  {
    result += " ";
  }

  result += val.second;
}

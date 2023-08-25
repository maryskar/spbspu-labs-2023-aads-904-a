#include "stringcreator.hpp"

#include <utility> 
#include <string>

void StringCreator::operator()(const std::pair< const long long, std::string >& key_value)
{
  result_ += " ";
  result_ += key_value.second;
}

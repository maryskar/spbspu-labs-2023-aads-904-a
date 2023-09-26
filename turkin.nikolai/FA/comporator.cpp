#include "comporator.hpp"

bool turkin::SortByFreq::operator()(const std::pair< char, node_t * > & lhs, const std::pair< char, node_t * > rhs)
{
  return lhs.second->data.second < rhs.second->data.second;
}

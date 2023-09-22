#include "comporator.hpp"

bool turkin::SortByFreq::operator()(const encoding_pair_t & lhs, const encoding_pair_t & rhs)
{
  return lhs.second < rhs.second;
}

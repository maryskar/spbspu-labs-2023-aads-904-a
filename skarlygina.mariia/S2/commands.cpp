#include "commands.h"
#include <iostream>
#include <stdexcept>

std::ostream& skarlygina::print(std::ostream& out, const std::string& name, const Dictis& dictis)
{
  auto it = dictis.cfind(name);
  if (it == dictis.cend())
  {
    throw std::invalid_argument("Unknown dictionary");
  }
  if (it->second.is_empty())
  {
    return out << "<EMPTY>" << std::endl;
  }
  out << name;
  for (auto&& data : it->second)
  {
    out << ' ' << data.first << ' ' << data.second;
  } 
  out << std::endl;
  return out;
}

skarlygina::Dictionary< int, std::string > skarlygina::complement(const std::string& lhs, const std::string& rhs, const Dictis& dictis)
{
  auto lhs_citerator = dictis.cfind(lhs);
  auto rhs_citerator = dictis.cfind(rhs);
  if ((lhs_citerator == dictis.cend()) || (rhs_citerator == dictis.cend()))
  {
    throw std::invalid_argument("Unknown dictionary");
  }
  if (lhs_citerator->second.is_empty() || rhs_citerator->second.is_empty())
  {
    return lhs_citerator->second;
  }

  auto returnable = lhs_citerator->second;
  auto rhs_iterator = rhs_citerator->second.cbegin();
  auto ret_iterator = returnable.begin();
  std::less< int > cmp;
  while ((ret_iterator != returnable.end()) && (rhs_iterator != rhs_citerator->second.cend()))
  {
    if (cmp(ret_iterator->first, rhs_iterator->first))
    {
      while ((ret_iterator != returnable.end()) && cmp(ret_iterator->first, rhs_iterator->first))
      {
        ++ret_iterator;
      }
    }
    else if (cmp(rhs_iterator->first, ret_iterator->first))
    {
      while ((rhs_iterator != rhs_citerator->second.cend()) && cmp(rhs_iterator->first, ret_iterator->first))
      {
        ++rhs_iterator;
      }
    }
    if ((ret_iterator == returnable.end()) || (rhs_iterator == rhs_citerator->second.cend()))
    {
      return returnable;
    }
    if (!cmp(ret_iterator->first, rhs_iterator->first) && !cmp(rhs_iterator->first, ret_iterator->first))
    {
      ++ret_iterator;
      returnable.pop(rhs_iterator->first);
      ++rhs_iterator;
    }
    else
    {
      ++ret_iterator;
      ++rhs_iterator;
    }
  }
  return returnable;
}

skarlygina::Dictionary< int, std::string > skarlygina::intersect(const std::string& lhs, const std::string& rhs, const Dictis& dictis)
{
  auto lhs_cit = dictis.cfind(lhs);
  auto rhs_cit = dictis.cfind(rhs);

  if ((lhs_cit == dictis.cend()) || (rhs_cit == dictis.cend()))
  {
    throw std::invalid_argument("Unknown dictionary");
  }
  if ((lhs_cit->second.is_empty()) || (rhs_cit->second.is_empty()))
  {
    return Dictionary< int, std::string >();
  }

  auto returnable = Dictionary< int, std::string >();
  auto lhs_iterator = lhs_cit->second.cbegin();
  auto rhs_iterator = rhs_cit->second.cbegin();
  std::less< int > cmp;
  while ((lhs_iterator != lhs_cit->second.cend()) && (rhs_iterator != rhs_cit->second.cend()))
  {
    if (cmp(lhs_iterator->first, rhs_iterator->first))
      while ((lhs_iterator != lhs_cit->second.cend()) && cmp(lhs_iterator->first, rhs_iterator->first))
      {
        ++lhs_iterator;
      }
    else if (cmp(rhs_iterator->first, lhs_iterator->first))
      while ((rhs_iterator != rhs_cit->second.cend()) && cmp(rhs_iterator->first, lhs_iterator->first))
      {
        ++rhs_iterator;
      }

    if ((lhs_iterator == lhs_cit->second.cend()) || (rhs_iterator == rhs_cit->second.cend()))
      return returnable;
    if (!cmp(lhs_iterator->first, rhs_iterator->first) && !cmp(rhs_iterator->first, lhs_iterator->first))
      returnable.push(lhs_iterator->first, lhs_iterator->second);

    ++lhs_iterator;
    ++rhs_iterator;
  }
  return returnable;
}

skarlygina::Dictionary< int, std::string > skarlygina::unite(const std::string& lhs, const std::string& rhs, const Dictis& dictis)
{
  auto lhs_citerator = dictis.cfind(lhs);
  auto rhs_citerator = dictis.cfind(rhs);

  if ((lhs_citerator == dictis.cend()) || (rhs_citerator == dictis.cend()))
    throw std::invalid_argument("Unknown dictionary");
  if (lhs_citerator->second.is_empty())
    return rhs_citerator->second;
  if (rhs_citerator->second.is_empty())
    return lhs_citerator->second;

  auto returnable = lhs_citerator->second;
  auto rhs_iterator = rhs_citerator->second.cbegin();
  while (rhs_iterator != rhs_citerator->second.cend())
  {
    if (returnable.cfind(rhs_iterator->first) == returnable.cend())
      returnable.push(rhs_iterator->first, rhs_iterator->second);
    ++rhs_iterator;
  }
  return returnable;
}

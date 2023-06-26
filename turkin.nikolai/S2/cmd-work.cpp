#include "cmd-work.hpp"

using dict = turkin::Dictionary< size_t, std::string, std::less< std::size_t > >;

void turkin::print(const std::pair< std::string, dict > & rhs, std::ostream & out)
{
  auto name = rhs.first;
  auto ret = rhs.second;
  if (ret.size() == 0)
  {
    out << "<EMPTY>\n";
  }
  out << name;
  for (auto ins = ret.cbegin(); ins != ret.cend(); ins++)
  {
    out << " " << ins->first << " " << ins->second;
  }
  out << " " << ret.cend()->first << " " << ret.cend()->second;
  out << "\n";
}

dict turkin::to_complement(const dict & one, const dict & two)
{
  dict result(one);
  for (auto ins = two.cbegin(); ins != two.cend(); ins++)
  {
    result.erase(ins->first);
  }
  return result;
}

dict turkin::to_intersect(const dict & one, const dict & two)
{
  dict result;
  for (auto it_first = two.cbegin(); it_first != two.cend(); it_first++)
  {
    auto res = two.cend();
    for (auto i = one.cbegin(); i != one.cend(); i++)
    {
      if (it_first->first == i->first)
        {
        res = i;
        break;
      }
    }
    if (res != two.cend())
    {
      result.emplace(std::make_pair(res->first, res->second));
    }
  }
  return result;
}

dict turkin::to_union(const dict & one, const dict & two)
{
  dict result;
  auto iter_second = two.cbegin();
  auto iter_second_end = two.cend();
  while (iter_second != iter_second_end)
  {
    result.emplace(std::make_pair(iter_second->first, iter_second->second));
    iter_second++;
  }
  auto iter_first = one.cbegin();
  auto iter_first_end = one.cend();
  while (iter_first != iter_first_end)
  {
    result.emplace(std::make_pair(iter_first->first, iter_first->second));
    iter_first++;
  }
  return result;
}

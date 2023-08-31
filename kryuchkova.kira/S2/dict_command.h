#ifndef DICT_COMMAND_H
#define DICT_COMMAND_H
#include <string>
#include <fstream>
#include "dictionary.h"
#include "out_messages.h"

namespace kryuchkova
{
  template< typename Key, typename Value, typename Compare >
  void print(const std::pair< std::string, Dictionary< Key, Value, Compare > > & rhs, std::ostream & out)
  {
    auto dict = rhs.second;
    auto cit = dict.cbegin();
    if (cit == dict.cend())
    {
      outEmpty(out);
      return;
    }
    out << rhs.first;
    while (cit != dict.cend())
    {
      out << " " << cit->first << " " << cit->second;
      cit++;
    }
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > make_comp(const Dictionary< Key, Value, Compare > & first_, const Dictionary< Key, Value, Compare > & second_)
  {
    Dictionary< Key, Value, Compare > res;
    if (std::addressof(first_) == std::addressof(second_)) 
    {
      return res;
    }
    auto iter_first_ = first_.cbegin();
    auto iter_second_ = second_.cbegin();
    Compare comp = Compare{};
    while (iter_first_ != first_.cend() && iter_second_ != second_.cend()) 
    {
      while (iter_second_ != second_.cend() && comp(iter_second_->first, iter_first_->first)) 
      {
        iter_second_++;
      }
      if (iter_second_ == second_.cend()) 
      {
        break;
      }
      if (iter_first_->first != iter_second_->first) 
      {
        res.insert(*iter_first_);
      }
      iter_first_++;
    }
    while (iter_first_ != first_.cend()) 
    {
      res.insert(*iter_first_);
      iter_first_++;
    }
    return res;
  }

}

#endif

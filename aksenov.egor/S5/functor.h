#ifndef FUNCTOR_H
#define FUNCTOR_H
#include <string>
#include <utility>
#include <iosfwd>
#include <stdexcept>

#include <checkOverflow.h>

namespace aksenov
{
  struct KeySummator
  {
    KeySummator():
      sum_(0)
    {}
    void operator()(const std::pair< long long, std::string > &pair)
    {
      if (aksenov::isOverflow(sum_, pair.first, '+'))
      {
        throw std::runtime_error("overflov");
      }
      sum_ += pair.first;
    }
    long long get() const
    {
      return sum_;
    }
  private:
    long long sum_;
  };

  struct StringSummator
  {
    StringSummator():
      str_("")
    {}
    void operator()(const std::pair< long long, std::string > &pair)
    {
      str_ += " " + pair.second;
    }
    std::string get() const
    {
      return str_;
    }
  private:
    std::string str_;
  };
}
#endif

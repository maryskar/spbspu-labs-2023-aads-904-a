#ifndef FUNCTOR_H
#define FUNCTOR_H
#include <string>
#include <utility>
#include <iosfwd>
#include "stdexcept"
#include <checkOverflow.h>

namespace aksenov
{
  struct keySummator
  {
    keySummator():
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
    long long get()
    {
      return sum_;
    }
    long long sum_;
  };
}
#endif

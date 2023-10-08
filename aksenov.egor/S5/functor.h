#ifndef FUNCTOR_H
#define FUNCTOR_H
#include <string>
#include <utility>
#include <iosfwd>

namespace aksenov
{
  struct Summator
  {
    Summator();
    void operator()(const std::pair< long long, std::string > &);
    long long res_;
    std::string finalStr_;
  };

  std::ostream &operator<<(std::ostream &, const Summator &);
}
#endif

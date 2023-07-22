#ifndef SUMMATOR_H
#define SUMMATOR_H

#include <utility>
#include <string>
#include <mathfunc.cpp>

namespace tarasenko
{
  class Summator
  {
  public:
   Summator():
     result_(0)
   {}
   void operator()(const std::pair< long long, std::string >& key_value)
   {
     result_ = summarize(result_, key_value.first);
   }
   long long getResult() const
   {
     return result_;
   }

  private:
   long long result_;
  };
}
#endif

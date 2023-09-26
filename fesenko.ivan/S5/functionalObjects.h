
#ifndef FUNCTIONALOBJECTS_H
#define FUNCTIONALOBJECTS_H
#include <utility>
#include <string>
namespace fesenko
{
  class NumSummator
  {
   public:
    NumSummator();
    void operator()(const std::pair< long long, std::string > &value_type);
    long long getSum() const;
   private:
    long long sum_;
  };

  class StrSummator
  {
   public:
    StrSummator();
    void operator()(const std::pair< long long, std::string > &value_type);
    std::string getSum() const;
   private:
    std::string sum_;
  };
}
#endif

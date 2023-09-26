#ifndef FUNCTIONALOBJECTS_H
#define FUNCTIONALOBJECTS_H
#include <utility>
#include <string>
namespace fesenko
{
  class Summator
  {
   public:
    Summator();
    void operator()(const std::pair< long long, std::string > &value_type);
    std::pair< long long, std::string > getSum() const;
   private:
    long long llSum_;
    std::string strSum_;
  };
}
#endif

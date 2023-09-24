#ifndef FUNCTIONALOBJECTS_H
#define FUNCTIONALOBJECTS_H
#include <utility>
#include <string>
namespace fesenko
{
  class StrSummator
  {
   public:
    StrSummator();
    void operator()(const std::pair< int, std::string > &value_type);
    std::string getSum() const;
   private:
    std::string sum_;
  };
}
#endif

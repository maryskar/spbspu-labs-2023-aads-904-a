#ifndef FUNCTIONALOBJECTS_H
#define FUNCTIONALOBJECTS_H
#include <utility>
#include <string>
namespace fesenko
{
  class IntSummator
  {
   public:
    IntSummator();
    void operator()(const std::pair< int, std::string > &value_type);
    int getSum() const;
   private:
    int sum_;
  };

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

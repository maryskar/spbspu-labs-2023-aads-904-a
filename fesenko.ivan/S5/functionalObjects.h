#ifndef FUNCTIONALOBJECTS_H
#define FUNCTIONALOBJECTS_H
namespace fesenko
{
  class StrSummator
  {
   public:
    StrSummator();
    void operator()(const std::pair< const int, std::string > &value_type);
    std::string getSum();
   private:
    std::string sum_;
  }
}
#endif

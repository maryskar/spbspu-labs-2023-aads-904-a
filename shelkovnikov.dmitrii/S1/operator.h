#ifndef SPBSPU_LABS_2023_AADS_904_A_OPERATOR_H
#define SPBSPU_LABS_2023_AADS_904_A_OPERATOR_H
#include <string>
namespace dimkashelk
{
  class Operator
  {
  public:
    explicit Operator(std::string &str);
  private:
    std::string operator_;
    bool isOperator();
  };
}
#endif

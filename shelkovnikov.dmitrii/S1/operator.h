#ifndef SPBSPU_LABS_2023_AADS_904_A_OPERATOR_H
#define SPBSPU_LABS_2023_AADS_904_A_OPERATOR_H
#include <string>
namespace dimkashelk
{
  class Operator
  {
  public:
    explicit Operator(const char str);
    bool isAdd();
    bool isSubtraction();
    bool isMultiplication();
    bool isDivision();
    bool isRemainder();
  private:
    char operator_;
    bool isOperator();
  };
}
#endif

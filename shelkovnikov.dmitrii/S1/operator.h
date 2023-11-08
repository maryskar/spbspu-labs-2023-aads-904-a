#ifndef SPBSPU_LABS_2023_AADS_904_A_OPERATOR_H
#define SPBSPU_LABS_2023_AADS_904_A_OPERATOR_H
#include <string>
namespace dimkashelk
{
  class Operator
  {
  public:
    explicit Operator(char c);
    bool isAdd() const;
    bool isSubtraction() const;
    bool isMultiplication() const;
    bool isDivision() const;
    bool isRemainder() const;
    static bool isOperator(char c);
  private:
    char operator_;
  };
}
#endif

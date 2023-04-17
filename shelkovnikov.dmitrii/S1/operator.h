#ifndef SPBSPU_LABS_2023_AADS_904_A_OPERATOR_H
#define SPBSPU_LABS_2023_AADS_904_A_OPERATOR_H
#include <string>
namespace dimkashelk
{
  class Operator
  {
  public:
    Operator() = default;
    Operator(const Operator &oper) = default;
    Operator(Operator &&oper) = default;
    explicit Operator(const std::string &str);
    ~Operator();
    Operator &operator=(const Operator &oper) = default;
    Operator &operator=(Operator &&oper) = default;
    bool isAdd();
    bool isSubtraction();
    bool isMultiplication();
    bool isDivision();
    bool isRemainder();
  private:
    std::string operator_;
    bool isOperator();
  };
}
#endif

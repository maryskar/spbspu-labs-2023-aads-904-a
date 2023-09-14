#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
namespace skarlygina
{
  long long sum(long long a, long long b);
  long long substraction(long long a, long long b);
  long long multiplication(long long a, long long b);
  long long division(long long a, long long b);
  long long remainder(long long a, long long b);
  bool isOperation(char op);
  bool isGreaterPriority(char op1, char op2);
  bool checkString(const std::string& op);
}
#endif

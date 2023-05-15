#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
namespace calculator
{
  long long sum(long long a, long long b);
  long long substraction(long long a, long long b);
  long long multiplication(long long a, long long b);
  long long division(long long a, long long b);
  long long remainder(long long a, long long b);
  bool isOperation(std::string op);
}
#endif

#include "calculate.h"
#include "mathOperations.h"
long long fesenko::calculate(long long a, long long b, std::string s)
{
  long long result = 0;
  if (s == "+") {
    result = summarize(a, b);
  }
  if (s == "-") {
    result = subtract(a, b);
  }
  if (s == "*") {
    result = multiply(a, b);
  }
  if (s == "/") {
    result = divide(a, b);
  }
  if (s == "%") {
    result == mod(a, b);
  }
  retutn result;
}

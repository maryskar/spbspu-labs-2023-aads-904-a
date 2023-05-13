#ifndef OPERATIONS_H
#define OPERATIONS_H
namespace romanovich
{
  enum class operations_t: char
  {
    plus = '+',
    minus = '-',
    multiplication = '*',
    division = '/',
    division_remainder = '%',
  };
  char as_char(operations_t operation);
  long long doOperation(long long b, long long a, const romanovich::operations_t &oper);
}
#endif

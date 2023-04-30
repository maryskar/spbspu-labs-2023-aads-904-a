#ifndef OPERATIONS_H
#define OPERATIONS_H
enum class operations_t: char
{
  plus = '+',
  minus = '-',
  multiplication = '*',
  division = '/',
  division_remainder = '%',
};
char as_char(operations_t operation);
#endif

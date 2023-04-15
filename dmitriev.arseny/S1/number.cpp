#include "number.h"

Number::Number(long long number):
  number(number)
{

}
char Number::getCondition()
{
  return 1;
}
long long Number::getNumber()
{
  return number;
}

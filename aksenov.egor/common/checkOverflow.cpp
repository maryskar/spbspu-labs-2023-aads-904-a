#include "checkOverflow.h"
#include <limits>
namespace aksenov
{
  const value maxVal = std::numeric_limits< value >::max();
  const value minVal = std::numeric_limits< value >::min();

  bool checkAddition(value op1, value op2)
  {
    bool overflow = (op1 > 0) && (op2 > maxVal - op1);
    bool underflow = (op1 < 0) && (op2 < minVal - op1);
    return overflow || underflow;
  }

  bool checkSubstract(value op1, value op2)
  {
    bool overflow = (op2 > 0) && (op1 < minVal + op1);
    bool underflow = (op2 < 0) && (op1 > minVal + op1);
    return overflow || underflow;
  }

  bool checkMultiplication(value op1, value op2)
  {
    if (op1 > 0)
    {
      if (op2 > 0)
      {
        return (op1 > (maxVal / op2));
      }
      else
      {
        return (op2 < (minVal / op1));
      }
    }
    else
    {
      if (op2 > 0)
      {
        return (op1 < (minVal / op2));
      }
      else
      {
        return (op1 != 0) && (op2 < (maxVal / op1));
      }
    }
  }

  bool checkModul(value op1, value op2)
  {
    return op1 == maxVal && op2 == -1;
  }

  bool checkDevision(value op1, value op2)
  {
    if (op2 == 0)
    {
      return false;
    }
    return op1 == maxVal && op2 == -1;
  }

  bool isOverflov(value op1, value, op2, char sign)
  {
    if (sign == '+')
    {
      return checkAddition(op1, op2);
    }
    else if (sign == '-')
    {
      return checkSubstract(op1, op2);
    }
    else if (sign == '*')
    {
      return checkMultiplication(op1, op2);
    }
    else if (sign == '/')
    {
      return checkDevision(op1, op2);
    }
    else if (sign == '%')
    {
      return checkModul(op1, op2);
    }
    else
    {
      return false;
    }
  }
}

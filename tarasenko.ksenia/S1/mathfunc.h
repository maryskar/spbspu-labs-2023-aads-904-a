#ifndef MATHFUNC_H
#define MATHFUNC_H
#include <stdexcept>
#include <limits>

template< typename T >
T sign(T val)
{
  return (val > 0) ? 1 : ((val < 0) ? -1 : 0);
}

template< typename T >
bool same_sign(T a, T b)
{
  return sign(a) * sign(b) > 0;
}

template< typename T >
T summarize(T a, T b)
{
  if (b > 0 && a > std::numeric_limits< T >::max() - b)
  {
    throw std::overflow_error("Overflow error");
  }
  if (b < 0 && a < std::numeric_limits< T >::min() - b)
  {
    throw std::overflow_error("Overflow error");
  }
  return a + b;
}

template< typename T >
T subtract(T a, T b)
{
  if (b < 0 && a > std::numeric_limits< T >::max() + b) {
    throw std::overflow_error("Overflow error");
  }
  if (b > 0 && a < std::numeric_limits< T >::min() + b) {
    throw std::overflow_error("Overflow error");
  }
  return a - b;
}

template< typename T >
T multiply(T a, T b)
{
  if (a == 0 || b == 0)
  {
    return 0;
  }
  if (same_sign< T >(a, b))
  {
    if (std::numeric_limits< T >::max() / b > a && b > 0)
    {
      return a * b;
    }
    else if (std::numeric_limits< T >::max() / b < a && b < 0)
    {
      return a * b;
    }
  }
  else
  {
    if (std::numeric_limits< T >::min() / b < a && b > 0)
    {
      return a * b;
    }
    else if (std::numeric_limits< T >::min() / b > a && b < 0)
    {
      return a * b;
    }
  }
  throw std::overflow_error("Overflow error");
}

template< typename T >
T divide(T a, T b)
{
  if (b == 0)
  {
    throw std::logic_error("Division by zero");
  }
  if (a == std::numeric_limits< T >::min() && b == -1)
  {
    throw std::logic_error("Overflow error");
  }
  return a / b;
}

template< typename T >
T mod(T a, T b)
{
  if (b == -1)
  {
    return 0;
  }
  T result = a % b;
  if (sign(result) * sign(b) < 0)
  {
    result = summarize< T >(result, b);
  }
  return result;
}
#endif

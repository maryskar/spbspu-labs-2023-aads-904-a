#ifndef DATA_TYPE_HPP
#define DATA_TYPE_HPP

#include <stdexcept>

namespace turkin
{
  namespace datatype
  {
    enum class PINF
    {
      LEFT_BRACKET = 40, RIGHT_BRACKET = 41, ADD = 43, SUB = 45, MUL = 42, DIV = 47, MOD = 37, NUM = 0
    };

    enum class PFIX
    {
      ADD = 43, SUB = 45, MUL = 42, DIV = 47, MOD = 37, NUM = 0
    };

    template< typename T >
    struct calc_t
    {
      calc_t(const calc_t< T > & rhs);
      calc_t(long long rhs, T nt);
      calc_t(char rhs, T nt);
      calc_t< T > & operator=(const calc_t< T > & rhs);
      union
      {
        long long num;
        char sign;
      } calc;
      T type;
    };
  };
};

template< typename T >
turkin::datatype::calc_t< T >::calc_t(const calc_t< T > & rhs):
  calc(rhs.calc),
  type(rhs.type)
{}

template< typename T >
turkin::datatype::calc_t< T >::calc_t(long long rhs, T nt):
  calc({.num=rhs}),
  type(nt)
{}

template< typename T >
turkin::datatype::calc_t< T >::calc_t(char rhs, T nt):
  calc({.sign=rhs}),
  type(nt)
{}

template< typename T >
turkin::datatype::calc_t< T > & turkin::datatype::calc_t< T >::operator=(const calc_t< T > & rhs)
{
  calc = rhs.calc;
  type = rhs.type;
  return * this;
}

#endif

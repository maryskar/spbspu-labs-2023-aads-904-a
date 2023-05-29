#ifndef DATA_TYPE_HPP
#define DATA_TYPE_HPP

namespace turkin
{
  namespace datatype
  {
    enum class PINF
    {
      ADD, SUB, MUL, DIV, MOD, NUM, LEFT_BRACKET, RIGHT_BRACKET
    };

    enum class PFIX
    {
      ADD, SUB, MUL, DIV, MOD, NUM
    };

    template< typename T >
    struct calc_t
    {
      calc_t(const calc_t< T > & rhs);
      calc_t(long long rhs, T nt);
      calc_t(char rhs, T nt);
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
  calc({ .num=rhs }),
  type(nt)
{}

template< typename T >
turkin::datatype::calc_t< T >::calc_t(char rhs, T nt):
  calc({ .sign=rhs }),
  type(nt)
{}

#endif

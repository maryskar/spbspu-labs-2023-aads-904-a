#ifndef DATA_TYPE_HPP
#define DATA_TYPE_HPP

namespace turkin
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
    public:
      calc_t(const calc_t< T > & rhs);
      calc_t(long long rhs, T nt);
      T & getType();
      const T & getType() const;
      long long & getNum();
      const long long & getNum() const;
    private:
      long long num;
      T type;
  };
};

template< typename T >
turkin::calc_t< T >::calc_t(const calc_t< T > & rhs):
  num(rhs.num),
  type(rhs.type)
{}

template< typename T >
turkin::calc_t< T >::calc_t(long long rhs, T nt):
  num(rhs),
  type(nt)
{}

template< typename T >
T & turkin::calc_t< T >::getType()
{
  return type;
}

template< typename T >
const T & turkin::calc_t< T >::getType() const
{
  return type;
}

template< typename T >
long long & turkin::calc_t< T >::getNum()
{
  return num;
}

template< typename T >
const long long & turkin::calc_t< T >::getNum() const
{
  return num;
}

#endif

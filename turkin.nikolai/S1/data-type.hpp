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
      long long num_;
      T type_;
  };
}

template< typename T >
turkin::calc_t< T >::calc_t(const calc_t< T > & rhs):
  num_(rhs.num_),
  type_(rhs.type_)
{}

template< typename T >
turkin::calc_t< T >::calc_t(long long rhs, T nt):
  num_(rhs),
  type_(nt)
{}

template< typename T >
T & turkin::calc_t< T >::getType()
{
  return type_;
}

template< typename T >
const T & turkin::calc_t< T >::getType() const
{
  return type_;
}

template< typename T >
long long & turkin::calc_t< T >::getNum()
{
  return num_;
}

template< typename T >
const long long & turkin::calc_t< T >::getNum() const
{
  return num_;
}

#endif

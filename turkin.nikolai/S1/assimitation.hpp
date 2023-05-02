#ifndef ASSIMILATION_HPP
#define ASSIMILATION_HPP

#include "data-type.hpp"

namespace turkin
{
  namespace assimilation
  {
    template< typename T >
    bool lt(const datatype::calc_t< T > & lhs, const datatype::calc_t< T > & rhs)
    {
      return (lhs.type == rhs.type) && (lhs.type == datatype::PINF::NUM) && (lhs.calc.num < rhs.calc.num);
    }

    template< typename T >
    bool gt(const datatype::calc_t< T > & lhs, const datatype::calc_t< T > & rhs)
    {
      return (lhs.type == rhs.type) && (lhs.type == datatype::PINF::NUM) && (lhs.calc.num > rhs.calc.num);
    }

    template< typename T >
    bool eq(const datatype::calc_t< T > & lhs, const datatype::calc_t< T > & rhs)
    {
      return (lhs.type == rhs.type) && (lhs.type == datatype::PINF::NUM) && (lhs.calc.num == rhs.calc.num);
    }

    template< typename T >
    bool lteq(const datatype::calc_t< T > & lhs, const datatype::calc_t< T > & rhs)
    {
      return (lhs.type == rhs.type) && (lhs.type == datatype::PINF::NUM) && (lhs.calc.num <= rhs.calc.num);
    }

    template< typename T >
    bool gteq(const datatype::calc_t< T > & lhs, const datatype::calc_t< T > & rhs)
    {
      return (lhs.type == rhs.type) && (lhs.type == datatype::PINF::NUM) && (lhs.calc.num >= rhs.calc.num);
    }

    template< typename T >
    bool neq(const datatype::calc_t< T > & lhs, const datatype::calc_t< T > & rhs)
    {
      return (lhs.type == rhs.type) && (lhs.type == datatype::PINF::NUM) && (lhs.calc.num != rhs.calc.num);
    }

    template< typename T >
    bool same(const datatype::calc_t< T > & lhs, const datatype::calc_t< T > & rhs)
    {
      return static_cast< datatype::PINF >(lhs.type) == static_cast< datatype::PINF >(rhs.type);
    }

    template< typename T >
    bool same(const datatype::calc_t< T > & lhs, T rhs)
    {
      return static_cast< datatype::PINF >(lhs.type) == static_cast< datatype::PINF >(rhs);
    }
  };

  namespace convert
  {
    datatype::calc_t< datatype::PINF > convertFIX2INF(const datatype::calc_t < datatype::PFIX > & rhs)
    {
      if (assimilation::same(rhs, datatype::PFIX::NUM))
      {
        return datatype::calc_t< datatype::PINF >(rhs.calc.num, static_cast< datatype::PINF >(rhs.type));
      }
      return datatype::calc_t< datatype::PINF >(rhs.calc.sign, static_cast< datatype::PINF >(rhs.type));
    }

    datatype::calc_t< datatype::PFIX > convertINF2FIX(const datatype::calc_t < datatype::PINF > & rhs)
    {
      if (assimilation::same(rhs, datatype::PINF::LEFT_BRACKET) || assimilation::same(rhs, datatype::PINF::RIGHT_BRACKET))
      {
        throw std::runtime_error("expression error");
      }
      if (assimilation::same(rhs, datatype::PINF::NUM))
      {
        return datatype::calc_t< datatype::PFIX >(rhs.calc.num, static_cast< datatype::PFIX >(rhs.type));
      }
      return datatype::calc_t< datatype::PFIX >(rhs.calc.sign, static_cast< datatype::PFIX >(rhs.type));
    }
  };
};

#endif

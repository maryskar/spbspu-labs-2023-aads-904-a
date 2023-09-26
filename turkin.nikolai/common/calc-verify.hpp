#ifndef CALC_VERIFY_HPP
#define CALC_VERIFY_HPP

namespace turkin
{
  bool isADDerror(long long lhs, long long rhs) noexcept;
  bool isSUBerror(long long lhs, long long rhs) noexcept;
  bool isMULerror(long long lhs, long long rhs) noexcept;
  bool isDIVerror(long long lhs, long long rhs) noexcept;
  bool isMODerror(long long lhs, long long rhs) noexcept;
}

#endif

#ifndef CUTOMTYPES_H
#define CUTOMTYPES_H

#include <string>

namespace dmitriev
{
  struct SeparatorIO
  {
    char expected;
  };

  std::istream& operator>>(std::istream& inp, SeparatorIO&& data);
  std::ostream& operator<<(std::ostream& out, const SeparatorIO& data);

  struct LableIO
  {
    std::string expected;
  };

  std::istream& operator>>(std::istream& inp, LableIO&& data);
  std::ostream& operator<<(std::ostream& out, const LableIO& data);

  struct DoubleI
  {
    double& value;
  };

  std::istream& operator>>(std::istream& inp, DoubleI&& data);

  struct DoubleO
  {
    const double& value;
  };

  std::ostream& operator<<(std::ostream& out, const DoubleO& data);

  struct LongLongI
  {
    long long& value;
  };

  std::istream& operator>>(std::istream& inp, LongLongI&& data);

  struct LongLongO
  {
    const long long& value;
  };

  std::ostream& operator<<(std::ostream& out, const LongLongO& data);

  struct StringI
  {
    std::string& value;
  };

  std::istream& operator>>(std::istream& inp, StringI&& data);

  struct StringO
  {
    const std::string& value;
  };

  std::ostream& operator<<(std::ostream& out, const StringO& data);
}

#endif

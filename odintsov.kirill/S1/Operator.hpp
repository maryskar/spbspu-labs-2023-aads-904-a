#ifndef OPERATOR_HPP
#define OPERATOR_HPP

namespace odintsov {
  long long add(long long lhs, long long rhs);
  long long subtract(long long lhs, long long rhs);
  long long multiply(long long lhs, long long rhs);
  long long divide(long long lhs, long long rhs);
  long long modulo(long long lhs, long long rhs);

  class Operator {
   public:
    long long (*const exec)(long long, long long);
    Operator(char o);
    bool operator>=(Operator& rhs) const;

   private:
    unsigned short priority_;
  };
}

#endif

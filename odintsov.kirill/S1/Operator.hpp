#ifndef OPERATOR_HPP
#define OPERATOR_HPP

namespace odintsov {
  double add(double lhs, double rhs);
  double subtract(double lhs, double rhs);
  double multiply(double lhs, double rhs);
  double divide(double lhs, double rhs);
  double modulo(double lhs, double rhs);

  class Operator {
   public:
    double (*const exec)(double, double);
    Operator(char o);
    bool operator>=(Operator& rhs) const;

   private:
    unsigned short priority_;
  };
}

#endif

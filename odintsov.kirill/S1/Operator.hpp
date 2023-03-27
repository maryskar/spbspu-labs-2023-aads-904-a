#ifndef OPERATOR_HPP
#define OPERATOR_HPP

namespace odintsov {
  class Operator {
   public:
    Operator(char o);
    bool operator>=(Operator& rhs) const;
    long long exec(long long lhs, long long rhs) const;

   private:
    long long (*exec_)(long long, long long);
    unsigned short priority_;
  };
}

#endif

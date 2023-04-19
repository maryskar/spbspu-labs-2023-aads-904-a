#ifndef OPERATOR_HPP
#define OPERATOR_HPP

namespace odintsov {
  class Operator {
   public:
    Operator(char o);
    bool operator<(const Operator& rhs) const;
    bool operator>(const Operator& rhs) const;
    bool operator<=(const Operator& rhs) const;
    bool operator>=(const Operator& rhs) const;
    long long exec(long long lhs, long long rhs) const;

   private:
    using funcPtr = long long (*)(long long, long long);
    funcPtr exec_;
    unsigned short priority_;
  };
}

#endif

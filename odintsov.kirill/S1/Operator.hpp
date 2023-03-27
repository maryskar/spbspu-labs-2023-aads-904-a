#ifndef OPERATOR_HPP
#define OPERATOR_HPP

namespace odintsov {
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

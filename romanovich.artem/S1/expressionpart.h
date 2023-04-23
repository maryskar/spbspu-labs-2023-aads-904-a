#ifndef EXPRESSION_PART_H
#define EXPRESSION_PART_H
#include "brackets.h"
#include "operations.h"
class ExpPart
{
public:
  explicit ExpPart(brackets_t br);
  explicit ExpPart(operations_t op);
  explicit ExpPart(long long op);
  bool isOperand() const;
  bool isOperation() const;
  bool isBracket() const;
  operations_t getOperation() const;
  long long int getOperand() const;
  brackets_t getBracket() const;
private:
  bool isOperation_;
  bool isBracket_;
  bool isOperand_;
  union ExpContent
  {
    explicit ExpContent(brackets_t br): bracket_(br) {};
    explicit ExpContent(operations_t op): operation_(op) {};
    explicit ExpContent(long long op): operand_(op) {}
    long long operand_;
    operations_t operation_;
    brackets_t bracket_;
  } content_;
};
#endif

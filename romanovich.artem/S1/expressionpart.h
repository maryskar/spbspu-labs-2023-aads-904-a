#ifndef EXPRESSION_PART_H
#define EXPRESSION_PART_H
#include "parenthesis.h"
#include "operations.h"
class ExpPart
{
public:
  explicit ExpPart(parenthesis_t pr);
  explicit ExpPart(operations_t op);
  explicit ExpPart(long long op);
  bool isOperand() const;
  bool isOperation() const;
  bool isParenthesis() const;
  operations_t getOperation() const;
  long long int getOperand() const;
  parenthesis_t getParenthesis() const;
private:
  bool isOperation_;
  bool isParenthesis_;
  bool isOperand_;
  union ExpContent
  {
    explicit ExpContent(parenthesis_t pr);
    explicit ExpContent(operations_t op);
    explicit ExpContent(long long op);
    long long operand_;
    operations_t operation_;
    parenthesis_t parenthesis_;
  } content_;
};
#endif

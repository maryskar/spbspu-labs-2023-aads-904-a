#ifndef MATHEXPRPTR_H
#define MATHEXPRPTR_H

#include "mathExpression.h"
#include "number.h"
#include "operator.h"
#include "parenthesis.h"

#include <string>

class MathExprPtr
{
public:
  MathExprPtr();
  MathExprPtr(std::string inp);
  MathExprPtr(const MathExprPtr& otherMathExprPtr) = delete;
  MathExprPtr(MathExprPtr&& otherMathExprPtr) noexcept;
  MathExprPtr& operator=(const MathExprPtr& otherMathExprPtr) = delete;
  MathExprPtr& operator=(MathExprPtr&& otherMathExprPtr) noexcept;
  Expression* getRawPointer() const;
  ~MathExprPtr();

private:
  Expression* adress;

};

#endif

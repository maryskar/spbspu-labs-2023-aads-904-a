#ifndef MATHEXPRPTR_H
#define MATHEXPRPTR_H

#include "mathExpression.h"
#include "number.h"
#include "operator.h"
#include "parenthesis.h"
#include <string>

namespace dmitriev
{
  class MathExprPtr
  {
  public:
    MathExprPtr();
    MathExprPtr(std::string inp);
    MathExprPtr(const MathExprPtr& otherMathExprPtr) = delete;
    MathExprPtr(MathExprPtr&& otherMathExprPtr) noexcept;
    MathExprPtr& operator=(const MathExprPtr& otherMathExprPtr) = delete;
    MathExprPtr& operator=(MathExprPtr&& otherMathExprPtr) noexcept;
    Expression* operator*();
    Expression* operator->();

    ~MathExprPtr();

  private:
    Expression* m_adress;

  };
}

#endif

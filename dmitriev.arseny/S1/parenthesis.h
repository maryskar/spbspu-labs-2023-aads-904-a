#ifndef PARENTHESIS_H
#define PARENTHESIS_H

#include "mathExpression.h"

namespace dmitriev
{
  class Parenthesis : public Expression
  {
  public:
    explicit Parenthesis(char m_parenthesis);
    Parenthesis(const Parenthesis& otherParenthesis);
    Parenthesis(Parenthesis&& otherParenthesis) noexcept;

    char getCondition() const override;
    bool isOpenParenthesis() const override;
    bool isCloseParenthesis() const override;

    bool isOpen() const;
    bool isClose() const;

  private:
    char m_parenthesis;

  };
}

#endif

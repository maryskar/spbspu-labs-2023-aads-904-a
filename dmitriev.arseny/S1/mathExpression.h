#ifndef MATHEXPRESSION_H
#define MATHEXPRESSION_H

namespace dmitriev
{
  class Expression
  {
  public:
    bool isNumber() const;
    bool isOperator() const;
    bool isParenthesis() const;

    virtual long long getNumber() const;
    virtual long long operator()(long long, long long);
    virtual bool operator==(Expression* otherExpr);
    virtual bool operator!=(Expression* otherExpr);
    virtual bool operator>(Expression* otherExpr);
    virtual bool operator<(Expression* otherExpr);
    virtual bool operator>=(Expression* otherExpr);
    virtual bool operator<=(Expression* otherExpr);
    virtual bool isOpenParenthesis() const;
    virtual bool isCloseParenthesis() const;

    virtual ~Expression() = default;
  private:
    virtual char getCondition() const = 0;
    virtual char getPriority() const;

  };
}

#endif

#ifndef MATHEXPRESSION_H
#define MATHEXPRESSION_H

class Expression
{
public:
  bool isNumber();
  bool isOperator();
  bool isParenthesis();

  virtual long long getNumber() = 0;
  virtual long long operator()(long long, long long) = 0;
  virtual bool isOpenParenthesis() = 0;
  virtual bool isCloseParenthesis() = 0;
  virtual char getPriority() = 0;

  virtual ~Expression() = default;
private:
  virtual char getCondition() = 0;

};

#endif

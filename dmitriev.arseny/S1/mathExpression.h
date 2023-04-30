#ifndef MATHEXPRESSION_H
#define MATHEXPRESSION_H

class Expression
{
public:
  bool isNumber() const;
  bool isOperator() const;
  bool isParenthesis() const;

  virtual long long getNumber();
  virtual long long operator()(long long, long long);
  virtual bool isOpenParenthesis();
  virtual bool isCloseParenthesis();
  virtual char getPriority();

  virtual ~Expression() = default;
private:
  virtual char getCondition() const = 0;

};

#endif

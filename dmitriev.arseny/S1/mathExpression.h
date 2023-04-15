#ifndef MATHEXPRESSION_H
#define MATHEXPRESSION_H

class Expression
{
public:
  bool isNumber();
  bool isOperator();
  bool isBracket();

  virtual ~Expression() = default;
private:
  virtual char getCondition() = 0;

};

#endif

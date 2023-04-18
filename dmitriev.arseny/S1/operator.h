#ifndef OPERATOR_H
#define OPERATOR_H

#include "mathExpression.h"

class Operator : public Expression
{
public:
	explicit Operator(char op);
	Operator(const Operator& otherOperator);
	Operator(Operator&& otherOperator);
	char getCondition() override;
	char getPriority() const;
	long long calculate(const long long& p1, const long long& p2);

private:
	long long (*mathOperator)(long long, long long);
	char priority;

};

#endif

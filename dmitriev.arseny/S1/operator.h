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
	long long getNumber() override;
	long long getOper(long long, long long) override;
	bool isOpenBracket() override;
	bool isCloseBracket() override;
	char getPriority() override;

private:
	long long (*mathOperator)(long long, long long);
	char priority;

};

#endif

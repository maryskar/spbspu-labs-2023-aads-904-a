#ifndef NUMBER_H
#define NUMBER_H

#include "mathExpression.h"

class Number : public Expression
{
public:
	explicit Number(long long number);
	Number(const Number& otherNumber);
	Number(Number&& otherNumber);

	char getCondition() override;
	long long getNumber() override;
	long long getOper(long long, long long) override;
	bool isOpenBracket() override;
	bool isCloseBracket() override;
	char getPriority() override;

private:
	long long number;

};

#endif

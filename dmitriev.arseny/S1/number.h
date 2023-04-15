#ifndef NUMBER_H
#define NUMBER_H

#include "mathExpression.h"

class Number : public Expression
{
public:
	explicit Number(long long number);
	char getCondition() override;
	long long getNumber();

private:
	long long number;

};

#endif

#ifndef BRACKET_H
#define BRACKET_H

#include "mathExpression.h"

class Bracket : public Expression
{
public:
	explicit Bracket(char bracket);
	char getCondition() override;
	bool isOpen();
	bool isClose();

private:
	char bracket;
};

#endif

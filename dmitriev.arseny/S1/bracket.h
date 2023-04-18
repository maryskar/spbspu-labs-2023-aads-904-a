#ifndef BRACKET_H
#define BRACKET_H

#include "mathExpression.h"

class Bracket : public Expression
{
public:
	explicit Bracket(char bracket);
	Bracket(const Bracket& otherBracket);
	Bracket(Bracket&& otherBracket);
	char getCondition() override;
	bool isOpen();
	bool isClose();

private:
	char bracket;
};

#endif

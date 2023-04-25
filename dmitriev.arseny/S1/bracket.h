#ifndef BRACKET_H
#define BRACKET_H

#include "mathExpression.h"

class Bracket : public Expression
{
public:
	Bracket() = default;
	explicit Bracket(char bracket);
	Bracket(const Bracket& otherBracket);
	Bracket(Bracket&& otherBracket);

	char getCondition() override;
	long long getNumber() override;
	long long getOper(long long, long long) override;
	bool isOpenBracket() override;
	bool isCloseBracket() override;
	char getPriority() override;

	bool isOpen();
	bool isClose();

private:
	char bracket;
};

#endif

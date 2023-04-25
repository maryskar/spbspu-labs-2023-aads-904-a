#ifndef MATHEXPRESSION_H
#define MATHEXPRESSION_H

class Expression
{
public:
	bool isNumber();
	bool isOperator();
	bool isBracket();

	virtual long long getNumber() = 0;
	virtual long long getOper(long long, long long) = 0;
	virtual bool isOpenBracket() = 0;
	virtual bool isCloseBracket() = 0;
	virtual char getPriority() = 0;

	virtual ~Expression() = default;
private:
	virtual char getCondition() = 0;

};

#endif

#include "number.h"
#include <iomanip>

Number::Number(long long number) :
	number(number)
{

}
Number::Number(const Number& otherNumber) :
	number(otherNumber.number)
{

}
Number::Number(Number&& otherNumber) :
	number(otherNumber.number)
{

}
char Number::getCondition()
{
	return 1;
}
long long Number::getNumber()
{
	return number;
}

long long Number::getOper(long long, long long)
{
	throw std::logic_error("logic_error");
}

bool Number::isOpenBracket()
{
	throw std::logic_error("logic_error");
}

bool Number::isCloseBracket()
{
	throw std::logic_error("logic_error");
}

char Number::getPriority()
{
	throw std::logic_error("logic_error");
}

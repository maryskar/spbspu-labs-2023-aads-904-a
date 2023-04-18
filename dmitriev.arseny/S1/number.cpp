#include "number.h"

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
long long Number::getLongLong()
{
	return number;
}

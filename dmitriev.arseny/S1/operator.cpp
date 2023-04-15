#include "operator.h"

#include <iomanip>
#include <limits>

long long plus(long long p1, long long p2);
long long minus(long long p1, long long p2);
long long multiple(long long p1, long long p2);
long long division(long long p1, long long p2);
long long mod(long long p1, long long p2);

auto defineOperator(char op)
{
	if (op == '+')
	{
		return plus;
	}
	else if (op == '-')
	{
		return minus;
	}
	else if (op == '*')
	{
		return multiple;
	}
	else if (op == '/')
	{
		return division;
	}
	else if (op == '%')
	{
		return mod;
	}
	else
	{
		throw std::logic_error("unknown operator");
	}
}


Operator::Operator(char op) :
	mathOperator(defineOperator(op)),
	priority(definePriority(op))
{

}

long long plus(long long p1, long long p2)
{
	if (p1 > max - p2 && p2 > 0)
	{
		throw std::overflow_error("overflow_error");
	}
	if (p1 < min - p2 && p2 < 0)
	{
		throw std::underflow_error("underflow_error");
	}

	return p2 + p1;
}

long long minus(long long p1, long long p2)
{
	if (p2 > max + p1 && p1 < 0)
	{
		throw std::overflow_error("overflow_error");
	}
	if (p2 < min + p1 && p1 > 0)
	{
		throw std::underflow_error("underflow_error");
	}

	return p2 - p1;
}

long long multiple(long long p1, long long p2)
{
	if ((p1 > max / p2 && p2 > 0) || (p1 > max / p2 && p2 < 0))
	{
		throw std::overflow_error("overflow_error");
	}
	if ((p1 > min / p2 && p2 < 0) || (p1 > max / p2 && p2 > 0))
	{
		throw std::underflow_error("underflow_error");
	}

	return p2 * p1;
}

long long division(long long p1, long long p2)
{
	if (p1 == 0)
	{
		throw std::logic_error("div on zero");
	}

	return p2 / p1;
}

long long mod(long long p1, long long p2)
{
	if (p1 == 0)
	{
		throw std::logic_error("mod on zero");
	}
	if ((p2 % p1) < 0)
	{
		return (p2 % p1) + p1;
	}
	return p2 % p1;
}

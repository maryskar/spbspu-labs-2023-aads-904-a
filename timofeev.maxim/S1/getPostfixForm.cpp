#include <stdexcept>
int getPriority(char op)
{
  if (op == '+' || op == '-')
  {
    return 1;
  }
  else if (op == '*' || op == '/' || op == '%')
  {
    return 2;
  }
  else
  {
    throw std::logic_error("No opperand in string");
  }
}
#include "functions.h"
bool dimkashelk::isPriorityOperation(char first, char second)
{
  return (first == '+' || first == '-') && (second == '*' || second == '/');
}

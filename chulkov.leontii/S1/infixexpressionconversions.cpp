#include "infixexpressionconversions.h"
#include "stack.h"
#include <string>

bool isOperator(char c){
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

int getPriority(char c){
  if (c == '+' || c == '-'){
    return 1;
  }
  else if (c == '*' || c == '/' || c == '%'){
    return 2;
  }
  return 0;
}
std::string infixToPostfix(std::string infixExpression){

}

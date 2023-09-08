#include <iostream>
#include <fstream>
#include <stdexcept>
#include "valueType.h"
#include "queue.h"
#include "stack.h"
#include "inputInfixQueue.h"
#include "divideExpression.h"
#include "countPostfixExpression.h"

using namespace potapova;

int main(int argc, char* argv[])
{
  std::istream* in_ptr = nullptr;
  if (argc == 2)
  {
    std::ifstream input_file;
    input_file.open(argv[1]);
    if (!input_file.is_open())
    {
      std::cerr << "Failed to open file\n";
      return 1;
    }
    in_ptr = &input_file;
  }
  else if (argc > 2)
  {
    std::cerr << "Incorrect number of arguments\n";
    return 1;
  }
  else
  {
    in_ptr = &std::cin;
  }
  expr_queue infix_expr;
  Stack< long long > answer_stack;
  *in_ptr >> std::ws;
  while (!in_ptr->eof())
  {
    if (!inputInfixQueue(infix_expr, *in_ptr))
    {
      std::cerr << "Input error\n";
      return 1;
    }
    try
    {
      expr_queue postfix_queue(composePostfixQueue(infix_expr));
      if (!postfix_queue.empty())
      {
        answer_stack.push(countPostfixExpression(postfix_queue));
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << "Error: " << e.what() << '\n';
      return 1;
    }
    *in_ptr >> std::ws;
  }
  while (answer_stack.size() > 1)
  {
    std::cout << answer_stack.top() << ' ';
    answer_stack.pop();
  }
  if (answer_stack.size() == 1)
  {
    std::cout << answer_stack.top();
  }
  std::cout << '\n';
  return 0;
}

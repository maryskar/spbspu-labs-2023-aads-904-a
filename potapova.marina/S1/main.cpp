#include <iostream>
#include <fstream>
#include <stdexcept>
#include "valueType.h"
#include "queue.h"
#include "stack.h"
#include "inputInfixQueue.h"
#include "divideExpression.h"
#include "getInputStream.h"
#include "countPostfixExpression.h"

int main()
{
  const char* argv[]{"", "C:/Users/79213/Desktop/Marina/UniversitySPBSPU/aip_labs/spbspu-labs-2023-aads-904-a/potapova.marina/S1/in.txt"};
  std::istream* in_ptr;
  potapova::expr_queue infix_expr;
  potapova::Stack< std::int64_t > answer_stack;
  try
  {
    in_ptr = potapova::getInputStream(2, argv);
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  while (!in_ptr->eof())
  {
    if (!inputInfixQueue(infix_expr, *in_ptr))
    {
      std::cerr << "Input error\n";
      return 1;
    }
    try
    {
      potapova::expr_queue postfix_queue(potapova::composePostfixQueue(infix_expr));
      if (!postfix_queue.empty())
      {
        answer_stack.push(potapova::countPostfixExpression(postfix_queue));
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << "Error: " << e.what() << '\n';
      return 1;
    }
    *in_ptr >> std::ws;
  }
  while (!answer_stack.empty())
  {
    std::cout << answer_stack.back() << ' ';
    answer_stack.pop();
  }
  return 0;
}

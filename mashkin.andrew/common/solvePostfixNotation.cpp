#include "solvePostfixNotation.h"
#include "queue.h"
#include "solving.h"
#include "stack.h"
#include <stdexcept>
#include <string>

void solve(mashkin::Stack< int long long >& solution, mashkin::Queue< std::string >& que)
{
  int long long fNum = 0;
  int long long sNum = 0;
  sNum = solution.getTop();
  solution.pop();
  fNum = solution.getTop();
  solution.pop();
  std::string operation = que.getHead();
  if (operation == "+")
  {
    solution.push(mashkin::sum(fNum, sNum));
  }
  else if (operation == "-")
  {
    solution.push(mashkin::minus(fNum, sNum));
  }
  else if (operation == "*")
  {
    solution.push(mashkin::multiplicate(fNum, sNum));
  }
  else if (operation == "/")
  {
    solution.push(mashkin::divide(fNum, sNum));
  }
  else if (operation == "%")
  {
    solution.push(mashkin::getRemainderAfterDivision(fNum, sNum));
  }
}

int long long mashkin::solvePostfixNotation(Queue< std::string >& que)
{
  mashkin::Stack< int long long > solution;
  while (que.isEmpty())
  {
    if (!que.getHead().find_first_of("()-+*%/"))
    {
      solve(solution, que);
      que.dequeue();
    }
    else
    {
      solution.push(std::stoll(que.getHead()));
      que.dequeue();
    }
  }
  return solution.getTop();
}

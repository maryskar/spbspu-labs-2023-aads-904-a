#include "solvePostfixNotation.h"
#include <stdexcept>
#include <string>
#include <queue.h>
#include <stack.h>
#include "solving.h"

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
    solution.push(mashkin::sum(fNum, sNum * (-1)));
  }
  else if (operation == "*")
  {
    solution.push(mashkin::multiplicate(fNum, sNum));
  }
  else if (operation == "/")
  {
    solution.push(fNum / sNum);
  }
  else if (operation == "%")
  {
    solution.push(mashkin::divide(fNum, sNum));
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

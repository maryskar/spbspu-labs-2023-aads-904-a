#include "solvePostfixNotation.h"
#include <stdexcept>
#include <string>
#include "queue.h"
#include "solving.h"
#include "stack.h"

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
  /*list_t< std::string >* list = nullptr;
  try
  {
    list = new list_t< std::string >{que.getHead(), nullptr};
    que.dequeue();
    list_t< std::string >* endList = list;
    if (que.isEmpty())
    {
      endList->next = new list_t< std::string >{que.getHead(), nullptr};
      que.dequeue();
      if (que.isEmpty())
      {
        endList->next->next = new list_t< std::string >{que.getHead(), nullptr};
        que.dequeue();
      }
      else
      {
        throw std::logic_error("Not enough arguments");
      }
    }
    else
    {
      std::string result = list->data;
      delete list;
      return result;
    }
    if (que.isEmpty())
    {
      endList = list->next->next;
      while (que.isEmpty())
      {
        endList->next = new list_t< std::string >{que.getHead(), nullptr};
        que.dequeue();
        endList = endList->next;
      }
      endList = list;
      while (list->next)
      {
        endList = solve(endList, list);
      }
    }
    else
    {
      endList = solve(endList, list);
    }
  }
  catch (const std::bad_alloc& ex)
  {
    list->clear();
    throw;
  }
  std::string result = list->data;
  delete list;*/
  return solution.getTop();
}

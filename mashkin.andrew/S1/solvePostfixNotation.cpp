#include "solvePostfixNotation.h"
#include <stdexcept>
#include <string>
#include "list.h"
#include "queue.h"

void setCorrectlyEndList(mashkin::list_t< std::string >* list, mashkin::list_t< std::string >* endList)
{
  if (endList != list)
  {
    endList = list;
    while (endList->next->next)
    {
      endList = endList->next;
    }
  }
}

void deleteSomeElem(mashkin::list_t< std::string >* endList)
{
  delete endList->next->next;
  delete endList->next;
  endList->next = nullptr;
}

void solve(mashkin::list_t< std::string >* endList, mashkin::list_t< std::string >* list)
{
  int fNum = std::stoi(endList->data);
  int sNum = std::stoi(endList->next->data);
  if (endList->next->next->data == "+")
  {
    endList->data = std::to_string(fNum + sNum);
  }
  else if (endList->next->next->data == "-")
  {
    endList->data = std::to_string(fNum - sNum);
  }
  else if (endList->next->next->data == "*")
  {
    endList->data = std::to_string(fNum * sNum);
  }
  else if (endList->next->next->data == "/")
  {
    endList->data = std::to_string(fNum / sNum);
  }
  else if (endList->next->next->data == "%")
  {
    endList->data = std::to_string(fNum % sNum);
  }
  else
  {
    return;
  }
  deleteSomeElem(endList);
  setCorrectlyEndList(list, endList);
}

std::string mashkin::solvePostfixNotation(Queue< std::string >& que)
{
  list_t< std::string >* list = new list_t< std::string >{que.drop(), nullptr};
  list_t< std::string >* endList = list;
  if (que.isEmpty())
  {
    endList->next = new list_t< std::string >{que.drop(), nullptr};
    if (que.isEmpty())
    {
      endList->next->next = new list_t< std::string >{que.drop(), nullptr};
    }
    else
    {
      throw std::logic_error("Not enough arguments");
    }
  }
  else
  {
    throw std::logic_error("Not enough arguments");
  }
  if (que.isEmpty())
  {
    while (que.isEmpty())
    {
      solve(endList, list);
      endList = endList->next;
      endList->next->next = new list_t< std::string >{que.drop(), nullptr};
    }
  }
  else
  {
    solve(endList, list);
  }
  return list->data;
}

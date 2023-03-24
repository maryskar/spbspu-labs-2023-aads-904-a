#include "solvePostfixNotation.h"
#include <stdexcept>
#include <string>
#include "list.h"
#include "queue.h"
#include "sumNum.h"

void deleteSomeElem(mashkin::list_t< std::string >* endList)
{
  if (endList->next->next->next)
  {
    mashkin::list_t< std::string >* var = endList->next->next->next;
    delete endList->next->next;
    delete endList->next;
    endList->next = var;
  }
  else
  {
    delete endList->next->next;
    delete endList->next;
    endList->next = nullptr;
  }
}

void clear(mashkin::list_t< std::string >* list)
{
  while (list)
  {
    mashkin::list_t< std::string >* toDelete = list;
    list = list->next;
    delete toDelete;
  }
}

mashkin::list_t< std::string >* solve(mashkin::list_t< std::string >* endList, mashkin::list_t< std::string >* list)
{
  int long long fNum = 0;
  int long long sNum = 0;
  try
  {
    fNum = std::stoll(endList->data);
    sNum = std::stoll(endList->next->data);
    if (!endList->next->next)
    {
      return endList;
    }
    else if (endList->next->next->data == "+")
    {
      endList->data = std::to_string(mashkin::sum(fNum, sNum));
    }
    else if (endList->next->next->data == "-")
    {
      endList->data = std::to_string(mashkin::sum(fNum, sNum * (-1)));
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
      endList = endList->next;
      return endList;
    }
  }
  catch (const std::exception& exception)
  {
    clear(list);
    throw;
  }
  deleteSomeElem(endList);
  endList = list;
  return endList;
}

std::string mashkin::solvePostfixNotation(Queue< std::string >& que)
{
  list_t< std::string >* list = nullptr;
  try
  {
    list = new list_t< std::string >{que.drop(), nullptr};
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
    if (que.isEmpty())
    {
      endList = list->next->next;
      while (que.isEmpty())
      {
        endList->next = new list_t< std::string >{que.drop(), nullptr};
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
    clear(list);
    throw;
  }
  std::string result = list->data;
  delete list;
  return result;
}

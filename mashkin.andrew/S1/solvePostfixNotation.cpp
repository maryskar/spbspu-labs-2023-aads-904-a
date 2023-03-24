#include "solvePostfixNotation.h"
#include <stdexcept>
#include <string>
#include "list.h"
#include "queue.h"

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

mashkin::list_t< std::string >* solve(mashkin::list_t< std::string >* endList, mashkin::list_t< std::string >* list)
{
  int fNum = std::stoi(endList->data);
  int sNum = std::stoi(endList->next->data);
  if (!endList->next->next)
  {
    return endList;
  }
  else if (endList->next->next->data == "+")
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
    endList = endList->next;
    return endList;
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
    else
    {
      throw std::logic_error("Not enough arguments");
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
    while (list)
    {
      list_t< std::string >* toDelete = list;
      list = list->next;
      delete toDelete;
    }
  }
  return list->data;
}

#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"
#include "stack.h"
#include "getPostfixForm.h"
#include "getValueOfPostfix.h"
void out(timofeev::Stack< long long >& res)
{
  while (!res.isEmpty())
  {
    std::cout << res.drop();
    res.pop();
    if (!res.isEmpty())
    {
      std::cout << " ";
    }
  }
}
int main(int argc, char* argv[])
{
  if (argc > 2)
  {
    std::cerr << "Error\n";
    return 1;
  }
  timofeev::Stack <long long> result;
  std::string str = "";
  if (argc == 1)
  {
    try
    {
      while (std::getline(std::cin, str))
      {
        if (!std::cin)
        {
          std::cerr << "Error" << "\n";
          return 1;
        }
        if (str.find_first_not_of(" \n") == std::string::npos)
        {
          continue;
        }
        timofeev::Queue <std::string> postfix = timofeev::getPostfixForm(str);
        result.push(timofeev::getValueOfPostfix(postfix));
      }
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  if (argc == 2)
  {
    try
    {
      std::ifstream File;
      File.open(argv[1]);
      if (!File.is_open())
      {
        std::cerr << "Error while open file" << "\n";
        return 2;
      }
      while (std::getline(File, str))
      {
       // std::getline(File, str);
        if (str.find_first_not_of(" \n") == std::string::npos)
        {
          continue;
        }
        timofeev::Queue <std::string> postfix = timofeev::getPostfixForm(str);
        result.push(timofeev::getValueOfPostfix(postfix));
      }
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  out(result);
  std::cout << "\n";
  return 0;
}

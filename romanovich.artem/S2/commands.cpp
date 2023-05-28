#include "commands.h"
#include <iostream>
#include <numeric>
namespace
{
  void printError()
  {
    std::cout << "<INVALID COMMAND>\n";
  }
  void tryCalcWithArg(const std::string &command, const std::vector< std::string > &polygons)
  {
    romanovich::CommandProcessor comProc;
    if (command.substr(0, comProc.complementCall.size() - 1) == comProc.complementCall)
    {
      //
    }
    else if (command.substr(0, comProc.intersectCall.size() - 1) == comProc.intersectCall)
    {
      //
    }
    else if (command.substr(0, comProc.unionCall.size() - 1) == comProc.unionCall)
    {
      //
    }
    else
    {
      printError();
    }
  }
}
namespace romanovich
{
  void CommandProcessor::operator()(const std::string &command, const std::vector< std::string > &polygons)
  {
    auto it = commands.find(command);
    if (it != commands.end())
    {
      (it->second)(polygons, "");
    }
    else
    {
      tryCalcWithArg(command, polygons);
    }
  }
}

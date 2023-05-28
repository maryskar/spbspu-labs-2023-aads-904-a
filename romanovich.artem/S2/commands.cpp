#include "commands.h"
#include <iostream>
#include <numeric>
namespace
{
  void printError()
  {
    std::cout << "<INVALID COMMAND>\n";
  }
  bool isThisCommand(const std::string &command, const std::string &procCommand)
  {
    return (command.substr(0, procCommand.size() - 1) == procCommand);
  }
  void tryCalcWithArg(const std::string &command, const std::vector< std::string > &polygons)
  {
    romanovich::CommandProcessor comProc;
    if (isThisCommand(command, comProc.complementCall))
    {
      //
    }
    else if (isThisCommand(command, comProc.intersectCall))
    {
      //
    }
    else if (isThisCommand(command, comProc.unionCall))
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
  void CommandProcessor::printCommand(const std::vector< std::string > &)
  {
  }
  void CommandProcessor::intersectCommand(const std::vector< std::string > &, const std::string &)
  {
  }
  void CommandProcessor::complementCommand(const std::vector< std::string > &, const std::string &)
  {
  }
  void CommandProcessor::unionCommand(const std::vector< std::string > &, const std::string &)
  {
  }
}

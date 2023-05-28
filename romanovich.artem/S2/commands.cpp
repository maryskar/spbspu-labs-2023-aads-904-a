#include "commands.h"
#include <iostream>
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
}
namespace romanovich
{
  void CommandProcessor::operator()(const std::string &command)
  {
    auto it = commands.find(command);
    if (it != commands.end())
    {
      //
    }
    else
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
  void CommandProcessor::printCommand(const std::vector< std::string > &)
  {
  }
  void CommandProcessor::intersectCommand(const std::vector< std::string > &)
  {
  }
  void CommandProcessor::complementCommand(const std::vector< std::string > &)
  {
  }
  void CommandProcessor::unionCommand(const std::vector< std::string > &)
  {
  }
}

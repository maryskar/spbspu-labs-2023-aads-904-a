#ifndef COMMANDS_H
#define COMMANDS_H
#include <unordered_map>
#include <iomanip>
#include <functional>
#include <vector>
using namespace std::placeholders;
namespace romanovich
{
  class CommandProcessor
  {
  public:
    std::string printCall = "print";
    std::string complementCall = "complement";
    std::string intersectCall = "intersect";
    std::string unionCall = "union";
    CommandProcessor()
    {
      commands[printCall] = std::bind(&CommandProcessor::printCommand, this, _1);
      commands[complementCall] = std::bind(&CommandProcessor::complementCommand, this, _1, _2);
      commands[intersectCall] = std::bind(&CommandProcessor::intersectCommand, this, _1, _2);
      commands[unionCall] = std::bind(&CommandProcessor::unionCommand, this, _1, _2);
    }
    void operator()(const std::string &command, const std::vector< std::string > &);
    void printCommand(const std::vector< std::string > &);
    void intersectCommand(const std::vector< std::string > &, const std::string &);
    void unionCommand(const std::vector< std::string > &, const std::string &);
    void complementCommand(const std::vector< std::string > &, const std::string &);
  private:
    std::unordered_map< std::string, std::function< void(const std::vector< std::string > &, std::string)>> commands;
  };
}
#endif

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
    void operator()(const std::string &);
    void printCommand(const std::vector< std::string > &);
    void intersectCommand(const std::vector< std::string > &);
    void unionCommand(const std::vector< std::string > &);
    void complementCommand(const std::vector< std::string > &);
    std::string printCall = "print";
    std::string complementCall = "complement";
    std::string intersectCall = "intersect";
    std::string unionCall = "union";
  private:
    std::unordered_map< std::string, const std::vector< std::string > & > commands;
  };
}
#endif

#include "commands.h"
namespace
{
  struct TreePrinter
  {
    void operator()(const romanovich::map_value_t data/*, std::ostream &out*/)
    {
      std::cout << data.second << "\n";
    }
  };
  struct LnrTraverse
  {
    void operator()(std::ostream &out, romanovich::map_t &map) const
    {
      out << "";
      TreePrinter treePrinter;
      map.traverseLnr(treePrinter);
    }
  };
}
namespace romanovich
{
  command_map_t createCommandDictionary()
  {
    std::string breadthCall = "breadth";
    command_map_t commands;
    using namespace std::placeholders;
    commands[breadthCall] = std::function< void(std::ostream &, map_t &) >(LnrTraverse());
    return commands;
  }
  void performCommand(std::ostream &out, map_t &map, const CommandHandler &operation)
  {
    operation(out, map);
  }
}
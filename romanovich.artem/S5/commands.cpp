#include "commands.h"
namespace
{
  struct ValuePrinter
  {
    void operator()(const romanovich::map_value_t &data/*, std::ostream &out*/)
    {
      std::cout << " " << data.second;
    }
  };
  struct KeySumCalc
  {
    static int calculate(const romanovich::map_t &map)
    {
      int total = 0;
      for (auto &data: map)
      {
        total += data.first;
      }
      return total;
    }
  };
  struct LnrTraverse
  {
    void operator()(std::ostream &out, const romanovich::map_t &map) const
    {
      out << KeySumCalc::calculate(map);
      ValuePrinter valuePrinter;
      map.traverseLnr(valuePrinter);
      out << "\n";
    }
  };
  struct RnlTraverse
  {
    void operator()(std::ostream &out, const romanovich::map_t &map) const
    {
      out << KeySumCalc::calculate(map);
      ValuePrinter valuePrinter;
      map.traverseRnl(valuePrinter);
      out << "\n";
    }
  };
  struct BreadthTraverse
  {
    void operator()(std::ostream &out, const romanovich::map_t &map) const
    {
      out << KeySumCalc::calculate(map);
      ValuePrinter valuePrinter;
      map.traverseBreadth(valuePrinter);
      out << "\n";
    }
  };
}
namespace romanovich
{
  command_map_t createCommandDictionary()
  {
    std::string lnrCall = "ascending";
    std::string rnlCall = "descending";
    std::string breadthCall = "breadth";
    command_map_t commands;
    commands[lnrCall] = std::function< void(std::ostream &, map_t &) >(LnrTraverse());
    commands[rnlCall] = std::function< void(std::ostream &, map_t &) >(RnlTraverse());
    commands[breadthCall] = std::function< void(std::ostream &, map_t &) >(BreadthTraverse());
    return commands;
  }
}
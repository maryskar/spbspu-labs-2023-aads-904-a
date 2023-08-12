#include "commands.h"
//#include <owerflowlongcheck.h>
#include "../common/owerflowlongcheck.h"
namespace
{
  bool isOverflow(long long a, long long b)
  {
    return (romanovich::overflowAdd(a, b) || romanovich::overflowSubt(a, b));
  }
  struct ValuePrinter
  {
    void operator()(const romanovich::map_value_t &data)
    {
      std::cout << " " << data.second;
    }
  };
  struct KeySumCalc
  {
    static long long calculate(const romanovich::map_t &map)
    {
      long long total = 0;
      for (auto &data: map)
      {
        if (isOverflow(total, data.first))
        {
          throw std::overflow_error("Overflow.");
        }
        total += data.first;
      }
      return total;
    }
  };
  struct LnrTraverse
  {
    void operator()(const romanovich::map_t &map) const
    {
      std::cout << KeySumCalc::calculate(map);
      ValuePrinter valuePrinter;
      map.traverseLnr(valuePrinter);
      std::cout << "\n";
    }
  };
  struct RnlTraverse
  {
    void operator()(const romanovich::map_t &map) const
    {
      std::cout << KeySumCalc::calculate(map);
      ValuePrinter valuePrinter;
      map.traverseRnl(valuePrinter);
      std::cout << "\n";
    }
  };
  struct BreadthTraverse
  {
    void operator()(const romanovich::map_t &map) const
    {
      std::cout << KeySumCalc::calculate(map);
      ValuePrinter valuePrinter;
      map.traverseBreadth(valuePrinter);
      std::cout << "\n";
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
    commands[lnrCall] = std::function< void(map_t &) >(LnrTraverse());
    commands[rnlCall] = std::function< void(map_t &) >(RnlTraverse());
    commands[breadthCall] = std::function< void(map_t &) >(BreadthTraverse());
    return commands;
  }
}

#include "commands.h"
using namespace std::placeholders;
namespace
{
  using map_ref = romanovich::map_t &;
  using const_map_ref = const romanovich::map_t &;
  struct ComplementOperation
  {
    void operator()(map_ref newDict,
                    const std::pair< std::string, romanovich::map_t > &firstDict,
                    const std::pair< std::string, romanovich::map_t > &secondDict) const
    {
      for (const auto &entry: firstDict.second)
      {
        if (secondDict.second.count(entry) == 0)
        {
          newDict[entry] = entry;
        }
      }
    }
  };
  struct IntersectOperation
  {
    void operator()(map_ref newDict,
                    const std::pair< std::string, romanovich::map_t > &firstDict,
                    const std::pair< std::string, romanovich::map_t > &secondDict) const
    {
      for (const auto &entry: firstDict.second)
      {
        if (secondDict.second.count(entry) > 0)
        {
          newDict[entry] = entry;
        }
      }
    }
  };
  struct UnionOperation
  {
    void operator()(map_ref newDict,
                    const std::pair< std::string, romanovich::map_t > &firstDict,
                    const std::pair< std::string, romanovich::map_t > &secondDict) const
    {
      for (auto &entry: secondDict.second)
      {
        newDict[entry] = entry;
      }
      for (auto &entry: firstDict.second)
      {
        newDict[entry] = entry;
      }
    }
  };
  std::ostream &printEmptyDict(std::ostream &out)
  {
    return out << "<EMPTY>";
  }
}
namespace romanovich
{
  std::unordered_map< std::string, CommandHandler > createCommandDictionary(container_t &map)
  {
    std::string printCall = "print";
    std::string complementCall = "complement";
    std::string intersectCall = "intersect";
    std::string unionCall = "union";
    std::unordered_map< std::string, CommandHandler > commands;
    commands[printCall] = std::bind(printCommand, _1, _2, std::ref(map));
    commands[complementCall] = std::bind(performCommand, _1, _2, std::ref(map), ComplementOperation());
    commands[intersectCall] = std::bind(performCommand, _1, _2, std::ref(map), IntersectOperation());
    commands[unionCall] = std::bind(performCommand, _1, _2, std::ref(map), UnionOperation());
    return commands;
  }
  void performCommand(std::istream &in, std::ostream &out, container_t &map,
                      const std::function< void(map_t &,
                                                const std::pair< std::string, map_t > &,
                                                const std::pair< std::string, map_t > &) > &operation)
  {
    std::string newDictName, mapName1, mapName2;
    in >> newDictName >> mapName1 >> mapName2;
    if (!in)
    {
      throw std::runtime_error("Error while reading command arguments.");
    }
    auto firstNodeValue = std::make_pair(mapName1, map_t());
    auto secondNodeValue = std::make_pair(mapName2, map_t());
    if (map.count(firstNodeValue) == 0 && map.count(secondNodeValue) == 0)
    {
      throw std::runtime_error("Error: both maps not found.");
    }
    if (map.count(firstNodeValue) == 0 || map.count(secondNodeValue) == 0)
    {
      std::string errDictName = map.count(firstNodeValue) == 0 ? mapName1 : mapName2;
      throw std::runtime_error("Error: map \"" + errDictName + "\" not found.");
    }
    if (map.empty())
    {
      printEmptyDict(out) << "\n";
    }
    else
    {
      const auto &map1 = map[firstNodeValue];
      const auto &map2 = map[secondNodeValue];
      map_t newDict;
      operation(newDict, map1, map2);
      map[{newDictName, map_t()}].second = newDict;
    }
  }
  void printCommand(std::istream &in, std::ostream &out, container_t &map)
  {
    std::string mapName;
    in >> mapName;
    if (!in)
    {
      throw std::runtime_error("Error while reading command arguments.");
    }
    auto nodeValue = std::make_pair(mapName, map_t());
    if (map.count(nodeValue) <= 0)
    {
      throw std::runtime_error("Error: map not found.");
    }
    else
    {
      const auto &mapData = map[nodeValue];
      if (mapData.second.empty())
      {
        printEmptyDict(out) << "\n";
      }
      else
      {
        out << mapName;
        for (const auto &item: mapData.second)
        {
          out << " " << item.first << " " << item.second;
        }
        out << "\n";
      }
    }
  }
}

#include "commands.h"
using namespace std::placeholders;
namespace
{
  using map_ref = romanovich::map_t &;
  using const_map_ref = const romanovich::map_t &;
  struct ComplementOperation
  {
    void operator()(map_ref newDict, const_map_ref firstDict, const_map_ref secondDict) const
    {
      if (firstDict.empty() || secondDict.empty())
      {
        return;
      }
      for (const auto &entry: firstDict)
      {
        if (secondDict.count(entry.first) == 0)
        {
          newDict[entry.first] = entry.second;
        }
      }
    }
  };
  struct IntersectOperation
  {
    void operator()(map_ref newDict, const_map_ref firstDict, const_map_ref secondDict) const
    {
      if (firstDict.empty() || secondDict.empty())
      {
        return;
      }
      for (const auto &entry: firstDict)
      {
        if (secondDict.count(entry.first) > 0)
        {
          newDict[entry.first] = entry.second;
        }
      }
    }
  };
  struct UnionOperation
  {
    void operator()(map_ref newDict, const_map_ref firstDict, const_map_ref secondDict) const
    {
      if (firstDict.empty())
      {
        newDict = secondDict;
        return;
      }
      if (secondDict.empty())
      {
        newDict = firstDict;
        return;
      }
      for (auto &entry: secondDict)
      {
        newDict[entry.first] = entry.second;
      }
      for (auto &entry: firstDict)
      {
        newDict[entry.first] = entry.second;
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
                      const std::function< void(map_t &, const map_t &, const map_t &) > &operation)
  {
    std::string newDictName, mapName1, mapName2;
    in >> newDictName >> mapName1 >> mapName2;
    if (!in)
    {
      throw std::runtime_error("Error while reading command arguments.");
    }
    if (map.count(mapName1) == 0 && map.count(mapName2) == 0)
    {
      throw std::runtime_error("Error: both mapionaries not found.");
    }
    if (map.count(mapName1) == 0 || map.count(mapName2) == 0)
    {
      std::string errDictName = map.count(mapName1) == 0 ? mapName1 : mapName2;
      throw std::runtime_error("Error: map \"" + errDictName + "\" not found.");
    }
    if (map.empty())
    {
      printEmptyDict(out) << "!\n";
    }
    else
    {
      const auto &map1 = map[mapName1];
      const auto &map2 = map[mapName2];
      map_t newDict;
      operation(newDict, map1, map2);
      map[newDictName] = newDict;
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
    if (map.count(mapName) <= 0)
    {
      throw std::runtime_error("Error: map not found.");
    }
    else
    {
      const auto &mapData = map[mapName];
      if (mapData.empty())
      {
        printEmptyDict(out) << "\n";
      }
      else
      {
        out << mapName;
        for (const auto &item: mapData)
        {
          out << " " << item.first << " " << item.second;
        }
        out << "\n";
      }
    }
  }
}

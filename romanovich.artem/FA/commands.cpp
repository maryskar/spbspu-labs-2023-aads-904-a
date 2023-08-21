#include "commands.h"
namespace
{
  void printDicts()
  {
    for (const auto &pair: *langDicts_)
    {
      std::cout << "Dict " << pair.first << ":\n";
      pair.second.print(std::cout);
    }
  }
}
romanovich::RedBlackTree< std::string, romanovich::CommandHandler > romanovich::createCommandDictionary(
  const HashTable *hashTable)
{
  hashTablePtr_ = const_cast<HashTable *>(hashTable);
  langDicts_ = new std::vector< std::pair< std::string, romanovich::HashTable >>;
  RedBlackTree< std::string, CommandHandler > commandDictionary;
  using namespace std::placeholders;
  commandDictionary["ad"] = std::bind(addDictCommand, _1);
  commandDictionary["aw"] = std::bind(addWordCommand, _1);
  commandDictionary["at"] = std::bind(addTranslation, _1);
  commandDictionary["rmw"] = std::bind(addTranslation, _1);
  commandDictionary["rmt"] = std::bind(addTranslation, _1);
  commandDictionary["w"] = std::bind(addTranslation, _1);
  commandDictionary["words"] = std::bind(addTranslation, _1);
  commandDictionary["cw"] = std::bind(addTranslation, _1);
  commandDictionary["ct"] = std::bind(addTranslation, _1);
  commandDictionary["export"] = std::bind(addTranslation, _1);
  commandDictionary["help"] = std::bind(addTranslation, _1);
  commandDictionary["exit"] = std::bind(addTranslation, _1);
  commandDictionary["amw"] = std::bind(addTranslation, _1);
  commandDictionary["cld"] = std::bind(addTranslation, _1);
  commandDictionary["md"] = std::bind(addTranslation, _1);
  return commandDictionary;
}
void romanovich::addWordCommand(std::istream &in)
{
  std::string word;
  std::string dictName;
  in >> word;
  in >> dictName;
  for (auto &pair: *langDicts_)
  {
    if (pair.first == dictName)
    {
      pair.second.addWord(word);
      pair.second.print(std::cout);
      return;
    }
  }
}
void romanovich::addDictCommand(std::istream &in)
{
  std::string dictName;
  in >> dictName;
  langDicts_->emplace_back(dictName, HashTable());
  printDicts();
}
void romanovich::addTranslation(std::istream &in)
{
  std::string word;
  std::string dictName;
  std::string translation;
  in >> word;
  in >> dictName;
  in >> translation;
  for (auto &pair: *langDicts_)
  {
    if (pair.first == dictName)
    {
      pair.second.addTranslation(word, translation);
      pair.second.print(std::cout);
      return;
    }
  }
}

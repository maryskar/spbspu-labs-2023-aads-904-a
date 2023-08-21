#include <limits>
#include "commands.h"
#include "../common/printmessages.h"
romanovich::CommandHandler::CommandHandler(std::istream &in):
  dictionaries_(new std::vector< std::pair< std::string, romanovich::HashTable >>),
  in_(in)
{
  using namespace std::placeholders;
  processor_["ad"] = std::bind(&CommandHandler::addDictCommand, this);
  processor_["aw"] = std::bind(&CommandHandler::addWordCommand, this);
  processor_["at"] = std::bind(&CommandHandler::addTranslation, this);
  processor_["rmw"] = std::bind(&CommandHandler::removeWord, this);
  processor_["rmt"] = std::bind(&CommandHandler::removeTranslation, this);
  processor_["w"] = std::bind(&CommandHandler::searchWord, this);
  processor_["words"] = std::bind(&CommandHandler::showAllWords, this);
  processor_["cw"] = std::bind(&CommandHandler::countWords, this);
  processor_["ct"] = std::bind(&CommandHandler::countTranslations, this);
  processor_["export"] = std::bind(&CommandHandler::exportToFile, this);
  processor_["help"] = std::bind(&CommandHandler::help, this);
  processor_["amw"] = std::bind(&CommandHandler::addMissingWords, this);
  processor_["cld"] = std::bind(&CommandHandler::createLevelDict, this);
  processor_["md"] = std::bind(&CommandHandler::mergeDicts, this);
}
void romanovich::CommandHandler::addWordCommand()
{
  std::string word;
  std::string dictName;
  in_ >> word;
  in_ >> dictName;
  for (auto &pair: *dictionaries_)
  {
    if (pair.first == dictName)
    {
      pair.second.addWord(word);
      pair.second.print(std::cout);
      break;
    }
  }
}
void romanovich::CommandHandler::addDictCommand()
{
  std::string dictName;
  in_ >> dictName;
  dictionaries_->emplace_back(dictName, HashTable());
  printDicts();
}
void romanovich::CommandHandler::addTranslation()
{
  std::string word;
  std::string dictName;
  std::string translation;
  in_ >> word;
  in_ >> dictName;
  in_ >> translation;
  for (auto &pair: *dictionaries_)
  {
    if (pair.first == dictName)
    {
      pair.second.addTranslation(word, translation);
      pair.second.print(std::cout);
      return;
    }
  }
}
void romanovich::CommandHandler::removeWord()
{
  std::string word;
  std::string dictName;
  in_ >> word;
  in_ >> dictName;
  for (auto &pair: *dictionaries_)
  {
    if (pair.first == dictName)
    {
      pair.second.removeWord(word);
      pair.second.print(std::cout);
      break;
    }
  }
}
void romanovich::CommandHandler::removeTranslation()
{
  std::string word;
  std::string dictName;
  std::string translation;
  in_ >> word;
  in_ >> dictName;
  in_ >> translation;
  for (auto &pair: *dictionaries_)
  {
    if (pair.first == dictName)
    {
      pair.second.removeTranslation(word, translation);
      pair.second.print(std::cout);
      break;
    }
  }
}
void romanovich::CommandHandler::searchWord()
{
}
void romanovich::CommandHandler::showAllWords()
{
}
void romanovich::CommandHandler::countWords()
{
}
void romanovich::CommandHandler::countTranslations()
{
}
void romanovich::CommandHandler::exportToFile()
{
}
void romanovich::CommandHandler::help()
{
}
void romanovich::CommandHandler::addMissingWords()
{
}
void romanovich::CommandHandler::createLevelDict()
{
}
void romanovich::CommandHandler::mergeDicts()
{
}
void romanovich::CommandHandler::printDicts()
{
  for (const auto &pair: *dictionaries_)
  {
    std::cout << "Dict " << pair.first << ":\n";
    pair.second.print(std::cout);
  }
}
void romanovich::CommandHandler::operator()(const std::string &command)
{
  constexpr auto maxLLSize = std::numeric_limits< std::streamsize >::max();
  try
  {
    processor_[command]();
  }
  catch (...)
  {
    printInvalidCommand(std::cout) << '\n';
    in_.ignore(maxLLSize, '\n');
  }
}
romanovich::CommandHandler::~CommandHandler()
{
  delete dictionaries_;
}

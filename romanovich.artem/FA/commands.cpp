#include <limits>
#include "commands.h"
#include "../common/printmessages.h"
romanovich::CommandHandler::CommandHandler(std::istream &in, std::ostream &out_):
  dictionaries_(new std::vector< std::pair< std::string, romanovich::HashTable >>),
  in_(in),
  out_(out_)
{
  using namespace std::placeholders;
  processor_["ad"] = std::bind(&CommandHandler::addDict, this);
  processor_["aw"] = std::bind(&CommandHandler::addWordToDict, this);
  processor_["at"] = std::bind(&CommandHandler::addTranslation, this);
  processor_["rmw"] = std::bind(&CommandHandler::removeWord, this);
  processor_["rmt"] = std::bind(&CommandHandler::removeTranslation, this);
  processor_["trans"] = std::bind(&CommandHandler::searchTranslations, this);
  processor_["words"] = std::bind(&CommandHandler::searchWords, this);
  processor_["cw"] = std::bind(&CommandHandler::countWords, this);
  processor_["ct"] = std::bind(&CommandHandler::countTranslations, this);
  processor_["export"] = std::bind(&CommandHandler::exportToFile, this);
  processor_["help"] = std::bind(&CommandHandler::help, this);
  processor_["amw"] = std::bind(&CommandHandler::addMissingWords, this);
  processor_["cld"] = std::bind(&CommandHandler::createLevelDict, this);
  processor_["md"] = std::bind(&CommandHandler::mergeDicts, this);
}
void romanovich::CommandHandler::addWordToDict()
{
  std::string word;
  std::string dictName;
  in_ >> word;
  in_ >> dictName;
  for (auto &pair: *dictionaries_)
  {
    if (pair.first == dictName)
    {
      pair.second.addKey(word);
      pair.second.print(out_);
      break;
    }
  }
}
void romanovich::CommandHandler::addDict()
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
      pair.second.addValue(word, translation);
      pair.second.print(out_);
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
      pair.second.removeKey(word);
      pair.second.print(out_);
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
      pair.second.removeValue(word, translation);
      pair.second.print(out_);
      break;
    }
  }
}
void romanovich::CommandHandler::searchTranslations()
{
  std::string word;
  std::string dictName;
  in_ >> word;
  in_ >> dictName;
  out_ << "Translations of \"" << word << "\" in dictionary \"" << dictName << "\":\n";
  for (auto &pair: *dictionaries_)
  {
    if (pair.first == dictName)
    {
      for (size_t i = 0; i < pair.second.getCapacity(); ++i)
      {
        const WordEntry &entry = pair.second.getData()[i];
        if (entry.translations.empty())
        {
          continue;
        }
        out_ << entry.translations[0];
        for (size_t j = 1; j < entry.translations.size(); ++j)
        {
          out_ << ", " << entry.translations[j];
        }
      }
      break;
    }
  }
  out_ << "\n";
}
void romanovich::CommandHandler::searchWords()
{
  std::string dictName;
  in_ >> dictName;
  out_ << "Words in dictionary \"" << dictName << "\":\n";
  for (auto &pair: *dictionaries_)
  {
    if (pair.first == dictName)
    {
      HashTable &table = pair.second;
      size_t capacity = table.getCapacity();
      size_t firstIndex = 0;
      while (firstIndex < capacity && table.getData()[firstIndex].word.empty())
      {
        ++firstIndex;
      }
      if (firstIndex < capacity)
      {
        out_ << table.getData()[firstIndex].word;
      }
      for (size_t i = firstIndex + 1; i < capacity; ++i)
      {
        if (!table.getData()[i].word.empty())
        {
          out_ << ", " << table.getData()[i].word;
        }
      }
      break;
    }
  }
  out_ << "\n";
}
void romanovich::CommandHandler::countWords()
{
  std::string dictName;
  in_ >> dictName;
  out_ << "Words count in dictionary \"" << dictName << "\": ";
  size_t count = 0;
  for (auto &pair: *dictionaries_)
  {
    auto data = pair.second.getData();
    for (size_t j = 1; j < data.size(); ++j)
    {
      count += !data[j].word.empty();
    }
  }
  out_ << count << "\n";
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
    out_ << "Dict " << pair.first << ":\n";
    pair.second.print(out_);
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
    printInvalidCommand(out_) << '\n';
    in_.ignore(maxLLSize, '\n');
  }
}
romanovich::CommandHandler::~CommandHandler()
{
  delete dictionaries_;
}

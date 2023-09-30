#include <limits>
#include <fstream>
#include <printmessages.h>
#include "commands.h"
romanovich::CommandHandler::CommandHandler(std::istream &in, std::ostream &out_):
  dictionaries_(DictionariesVault::instance()),
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
  printDicts(out_);
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
      if (!data[j].word.empty())
      {
        ++count;
      }
    }
  }
  out_ << count << "\n";
}
void romanovich::CommandHandler::countTranslations()
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
      count += data[j].translations.size();
    }
  }
  out_ << count << "\n";
}
void romanovich::CommandHandler::exportToFile()
{
  std::string fileName;
  in_ >> fileName;
  std::ofstream file(fileName + ".txt");
  printDicts(file);
  file.close();
}
void romanovich::CommandHandler::help()
{
  out_ << "Available commands:\n";
  out_ << "ad <dict> - add a new dictionary\n";
  out_ << "aw <word> <dict> - add a new word to dictionaries\n";
  out_ << "at <word> <dict> <translation> - add a new translation to a word\n";
  out_ << "rmw <word> <dict> - remove a word from dictionaries\n";
  out_ << "rmt <word> <dict> <translation> - remove a translation from a word\n";
  out_ << "w <word> <dict> - search for a word in a dictionary\n";
  out_ << "words <dict> - show all words in a dictionary\n";
  out_ << "cw <dict> - count the number of words in dictionaries\n";
  out_ << "ct <word> <dict> - count the number of translations for a word\n";
  out_ << "export <dict> <file> - export dictionary to a file\n";
  out_ << "help - display available commands\n";
  out_ << "amw <dict-from> <dict-to> - add all missing words from one dictionary to another\n";
  out_ << "cld <level> <dict> - create/update level dictionary\n";
  out_ << "md <dict> - merge dictionaries\n";
}
void romanovich::CommandHandler::addMissingWords()
{
  std::string dictFrom;
  std::string dictTo;
  in_ >> dictFrom;
  in_ >> dictTo;
  for (auto &pair1: *dictionaries_)
  {
    if (pair1.first == dictFrom)
    {
      for (auto &pair2: *dictionaries_)
      {
        if (pair2.first == dictTo)
        {
          pair2.second.addWordsFromAnother(pair1.second);
          out_ << "Added missing words from dictionary '" << dictFrom << "' to dictionary '" << dictTo << "'\n";
          return;
        }
      }
      out_ << "Dictionary '" << dictTo << "' not found.\n";
      return;
    }
  }
  out_ << "Dictionary '" << dictFrom << "' not found.\n";
}
void romanovich::CommandHandler::createLevelDict()
{
  std::string dict;
  std::string newDictName;
  in_ >> dict;
  in_ >> newDictName;
  std::pair< std::string, romanovich::HashTable > newDict;
  newDict.first = newDictName;
  for (auto &pair: *dictionaries_)
  {
    if (pair.first == dict)
    {
      newDict.second.addLevelWordsFromAnother(pair.second);
      out_ << "Added level words from dictionary '" << dict << "'\n";
      dictionaries_->push_back(newDict);
      return;
    }
  }
  out_ << "Dictionary '" << dict << "' not found.\n";
}
void romanovich::CommandHandler::mergeDicts()
{
  std::string dict1;
  std::string dict2;
  std::string newDictName;
  in_ >> dict1;
  in_ >> dict2;
  in_ >> newDictName;
  std::pair< std::string, romanovich::HashTable > newDict;
  newDict.first = newDictName;
  for (auto &pair1: *dictionaries_)
  {
    if (pair1.first == dict1)
    {
      newDict.second.addWordsFromAnother(pair1.second);
      out_ << "Added missing words from dictionary '" << dict1 << "'\n";
      dictionaries_->push_back(newDict);
    }
    out_ << "Dictionary '" << dict1 << "' not found.\n";
  }
  for (auto &pair2: *dictionaries_)
  {
    if (pair2.first == dict2)
    {
      newDict.second.addWordsFromAnother(pair2.second);
      out_ << "Added missing words from dictionary '" << dict2 << "'\n";
      return;
    }
    out_ << "Dictionary '" << dict2 << "' not found.\n";
  }
}
void romanovich::CommandHandler::printDicts(std::ostream &out)
{
  for (const auto &pair: *dictionaries_)
  {
    out << "Dict " << pair.first << ":\n";
    pair.second.print(out);
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

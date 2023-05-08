#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <string>
#include "murmurhash2.h"
struct Command
{
  enum class CommandList
  {
    invalid_command,
    add_dict,
    add_word,
    add_translation,
    remove_word,
    remove_translation,
    search_word,
    show_all_words,
    count_words,
    count_translations,
    export_to_file,
    help,
    add_missing_words,
    create_level_dict,
    merge_dicts
  };
};
void executeCommand(Command::CommandList command, std::string parametersLine)
{
  if (command == Command::CommandList::add_word)
  {
    std::cout << parametersLine << " " << generateMurmurHash2(parametersLine, 0x5bd1e995, 24) << "\n";
  }
}
void commandFromString(const std::string &str)
{
  int intBegin = 0;
  int intEnd = str.find(' ');
  if (intEnd != -1)
  {
    ///
  }
  std::string commandStr = str.substr(intBegin, intEnd - intBegin);
  std::string parametersLine = str.substr(intEnd - intBegin + 1);
  if (commandStr == "add_dict" || commandStr == "ad")
  {
    executeCommand(Command::CommandList::add_dict, std::string());
  }
  else if (commandStr == "add_word" || commandStr == "aw")
  {
    executeCommand(Command::CommandList::add_word, parametersLine);
  }
  else if (commandStr == "add_translation" || commandStr == "at")
  {
    executeCommand(Command::CommandList::add_translation, std::string());
  }
  else if (commandStr == "remove_word" || commandStr == "rw")
  {
    executeCommand(Command::CommandList::remove_word, std::string());
  }
  else if (commandStr == "remove_translation" || commandStr == "rt")
  {
    executeCommand(Command::CommandList::remove_translation, std::string());
  }
  else if (commandStr == "search_word" || commandStr == "w")
  {
    executeCommand(Command::CommandList::search_word, std::string());
  }
  else if (commandStr == "show_all_words" || commandStr == "words")
  {
    executeCommand(Command::CommandList::show_all_words, std::string());
  }
  else if (commandStr == "count_words" || commandStr == "cw")
  {
    executeCommand(Command::CommandList::count_words, std::string());
  }
  else if (commandStr == "count_translations" || commandStr == "ct")
  {
    executeCommand(Command::CommandList::count_translations, std::string());
  }
  else if (commandStr == "export")
  {
    executeCommand(Command::CommandList::export_to_file, std::string());
  }
  else if (commandStr == "help")
  {
    executeCommand(Command::CommandList::help, std::string());
  }
  else if (commandStr == "add_missing_words" || commandStr == "amw")
  {
    executeCommand(Command::CommandList::add_missing_words, std::string());
  }
  else if (commandStr == "create_level_dict" || commandStr == "cld")
  {
    executeCommand(Command::CommandList::create_level_dict, std::string());
  }
  else if (commandStr == "merge_dicts" || commandStr == "md")
  {
    executeCommand(Command::CommandList::merge_dicts, std::string());
  }
  else
  {
    std::cout << "Invalid command: " + commandStr + "\n";
  }
}
#endif

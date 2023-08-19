//#ifndef COMMAND_H
//#define COMMAND_H
//#include <iostream>
//#include <string>
//#include "murmurhash2.h"
//#include "dict.h"
//#include "../common/rstrings.h"
//struct Command
//{
//  enum class CommandList
//  {
//    add_dict,
//    add_word,
//    add_translation,
//    remove_word,
//    remove_translation,
//    search_word,
//    show_all_words,
//    count_words,
//    count_translations,
//    export_to_file,
//    help,
//    add_missing_words,
//    create_level_dict,
//    merge_dicts
//  };
//};
//void addWord(HashTable &hashTable, const std::string &word)
//{
//  uint32_t hashValue = generateMurmurHash2(word, 0x5bd1e995, 24);
//  uint32_t index = hashValue % hashTable.capacity_;
//  hashTable.data_[index] = {word, {}};
//  hashTable.print();
//}
//void executeCommand(Command::CommandList command, const std::string &argument, HashTable &hashTable)
//{
//  if (command == Command::CommandList::add_word)
//  {
//    addWord(hashTable, argument);
//  }
//  if (command == Command::CommandList::add_dict)
//  {
//    Dict dict{argument, {}};
//    std::cout << "Dict created: " + argument + "\n";
//  }
//}
//void processCommand(const std::string &str, HashTable hashTable)
//{
//  const char sep = ' ';
//  int intBegin = 0;
//  int intEnd = str.find(sep);
//  std::string commandStr = str.substr(intBegin, intEnd - intBegin);
//  std::string parametersLine = str.substr(intEnd - intBegin + 1); //проверить что когда одно слова это ""
//  trim(parametersLine);
//  for (size_t i = 0, j = 0; i != std::string::npos; i = j)
//  {
//    std::string argument = parametersLine.substr(i + (i != 0), (j = parametersLine.find(sep, i + 1)) - i - (i != 0));
//    if (commandStr == "add_dict" || commandStr == "ad")
//    {
//      executeCommand(Command::CommandList::add_dict, argument, hashTable);
//    }
//    else if (commandStr == "add_word" || commandStr == "aw")
//    {
//      executeCommand(Command::CommandList::add_word, argument, hashTable);
//    }
//    else if (commandStr == "add_translation" || commandStr == "at")
//    {
//      executeCommand(Command::CommandList::add_translation, argument, hashTable);
//    }
//    else if (commandStr == "remove_word" || commandStr == "rw")
//    {
//      executeCommand(Command::CommandList::remove_word, argument, hashTable);
//    }
//    else if (commandStr == "remove_translation" || commandStr == "rt")
//    {
//      executeCommand(Command::CommandList::remove_translation, argument, hashTable);
//    }
//    else if (commandStr == "search_word" || commandStr == "w")
//    {
//      executeCommand(Command::CommandList::search_word, argument, hashTable);
//    }
//    else if (commandStr == "show_all_words" || commandStr == "words")
//    {
//      executeCommand(Command::CommandList::show_all_words, argument, hashTable);
//    }
//    else if (commandStr == "count_words" || commandStr == "cw")
//    {
//      executeCommand(Command::CommandList::count_words, argument, hashTable);
//    }
//    else if (commandStr == "count_translations" || commandStr == "ct")
//    {
//      executeCommand(Command::CommandList::count_translations, argument, hashTable);
//    }
//    else if (commandStr == "export")
//    {
//      executeCommand(Command::CommandList::export_to_file, argument, hashTable);
//    }
//    else if (commandStr == "help")
//    {
//      executeCommand(Command::CommandList::help, argument, hashTable);
//    }
//    else if (commandStr == "add_missing_words" || commandStr == "amw")
//    {
//      executeCommand(Command::CommandList::add_missing_words, argument, hashTable);
//    }
//    else if (commandStr == "create_level_dict" || commandStr == "cld")
//    {
//      executeCommand(Command::CommandList::create_level_dict, argument, hashTable);
//    }
//    else if (commandStr == "merge_dicts" || commandStr == "md")
//    {
//      executeCommand(Command::CommandList::merge_dicts, argument, hashTable);
//    }
//    else
//    {
//      std::cout << "Invalid command: " + commandStr + "\n";
//    }
//  }
//}
//#endif

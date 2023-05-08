#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <string>
struct Command
{
  enum class Commands
  {
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
  Commands command;
  Commands stringToCommand(const std::string &str);
};
Command::Commands Command::stringToCommand(const std::string &str)
{
  if (str == "add_dict" || str == "ad")
  {
    return Commands::add_dict;
  }
  else if (str == "add_word" || str == "aw")
  {
    return Commands::add_word;
  }
  else if (str == "add_translation" || str == "at")
  {
    return Commands::add_translation;
  }
  else if (str == "remove_word" || str == "rw")
  {
    return Commands::remove_word;
  }
  else if (str == "remove_translation" || str == "rt")
  {
    return Commands::remove_translation;
  }
  else if (str == "search_word" || str == "w")
  {
    return Commands::search_word;
  }
  else if (str == "show_all_words" || str == "words")
  {
    return Commands::show_all_words;
  }
  else if (str == "count_words" || str == "cw")
  {
    return Commands::count_words;
  }
  else if (str == "count_translations" || str == "ct")
  {
    return Commands::count_translations;
  }
  else if (str == "export")
  {
    return Commands::export_to_file;
  }
  else if (str == "help")
  {
    return Commands::help;
  }
  else if (str == "add_missing_words" || str == "amw")
  {
    return Commands::add_missing_words;
  }
  else if (str == "create_level_dict" || str == "cld")
  {
    return Commands::create_level_dict;
  }
  else if (str == "merge_dicts" || str == "md")
  {
    return Commands::merge_dicts;
  }
  else
  {
    throw std::invalid_argument("Invalid Commands: " + str);
  }
}
#endif

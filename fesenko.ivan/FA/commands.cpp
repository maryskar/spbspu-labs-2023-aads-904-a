#include "commands.h"
#include <stdexcept>
#include <string>
#include <messages.h>
#include "subCommands.h"

fesenko::Commands::Commands():
  type1(),
  type2()
{
  type1.insert(std::make_pair("read_file", read_file_cmd));
  type1.insert(std::make_pair("delete_dict", delete_dict_cmd));
  type1.insert(std::make_pair("delete_word", delete_word_cmd));
  type1.insert(std::make_pair("complement", complement_cmd));
  type1.insert(std::make_pair("intersect", intersect_cmd));
  type1.insert(std::make_pair("union", union_cmd));
  type1.insert(std::make_pair("rename", rename_cmd));
  type1.insert(std::make_pair("insert", insert_cmd));

  type2.insert(std::make_pair("find", &find_cmd));
  type2.insert(std::make_pair("print_dict", &print_dict_cmd));
  type2.insert(std::make_pair("print_word", &print_word_cmd));
}

void fesenko::Commands::make(const std::string &command, data_t &data, std::istream &in, std::ostream &out)
{
  try {
    if (type1.find(command)) {
      if (type1[command].word == command) {
        type1.at(command).data(data, in);
        return;
      } else if (!type1[command].collision_list.empty()) {
        for (auto &it : type1[command].collision_list) {
          if (it.first == command) {
            it.second(data, in);
            return;
          }
        }
      }
    }
    if (type2.find(command)) {
      if (type2[command].word == command) {
        type2.at(command).data(data, in, out);
        return;
      } else if (!type2[command].collision_list.empty()) {
        for (auto &it : type2[command].collision_list) {
          if (it.first == command) {
            it.second(data, in, out);
            return;
          }
        }
      }
    }
    throw std::logic_error("No command");
  } catch (...) {
    outInvalidCommandMessage(out);
    out << "\n";
  }
}

#include "subCommands.h"
#include <string>
#include <fstream>
#include <stdexcept>
#include "subFunctions.h"

void fesenko::read_file_cmd(data_t &data, std::istream &in)
{
  std::string line = "";
  std::getline(in, line);
  std::string dict_name = get_cmd_word(line);
  std::string filename = get_cmd_word(line);
  if (!line.empty()) {
    throw std::invalid_argument("Wrong input");
  }
  std::ifstream fin(filename);
  if (!fin.is_open()) {
    throw std::invalid_argument("Can`t open the file");
  }
  data[dict_name].data.clear();
  hash_t &dict = data.at(dict_name).data;
  data.insert(dict_name);
  size_t counter = 0;
  ForwardList< std::string > word_list;
  while (std::getline(fin, line)) {
    counter++;
    word_list = parse_text_line(line);
    std::string word = "";
    while (!word_list.empty()) {
      word = word_list.front();
      word_list.pop_front();
      dict.insert(word);
      if (dict[word].word == word) {
        insert_in_asc_order(dict[word].data, counter);
      } else {
        for (auto &it: dict[word].collision_list) {
          if (it.first == word) {
            insert_in_asc_order(it.second, counter);
          }
        }
      }
    }
  }
}

void fesenko::delete_dict_cmd(data_t &data, std::istream &in)
{
  std::string line = "";
  std::getline(in, line);
  std::string dict_name = get_cmd_word(line);
  if (!line.empty()) {
    throw std::invalid_argument("Wrong input");
  }
  data.erase(dict_name);
}

void fesenko::delete_word_cmd(data_t &data, std::istream &in)
{
  std::string line = "";
  std::getline(in, line);
  std::string dict_name = get_cmd_word(line);
  std::string word = get_cmd_word(line);
  if (!line.empty()) {
    throw std::invalid_argument("Wrong input");
  }
  data.at(dict_name).data.erase(word);
}

void fesenko::complement_cmd(data_t &data, std::istream &in)
{
  std::string line = "";
  std::getline(in, line);
  std::string new_dict_name = get_cmd_word(line);
  std::string dict_name1 = get_cmd_word(line);
  std::string dict_name2 = get_cmd_word(line);
  make_complementation(data, new_dict_name, dict_name1, dict_name2);
  while (!line.empty()) {
    std::string dict_name = get_cmd_word(line);
    make_complementation(data, new_dict_name, new_dict_name, dict_name);
  }
}

void fesenko::intersect_cmd(data_t &data, std::istream &in)
{
  std::string line = "";
  std::getline(in, line);
  std::string new_dict_name = get_cmd_word(line);
  std::string dict_name1 = get_cmd_word(line);
  std::string dict_name2 = get_cmd_word(line);
  make_intersection(data, new_dict_name, dict_name1, dict_name2);
  while (!line.empty()) {
    std::string dict_name = get_cmd_word(line);
    make_intersection(data, new_dict_name, new_dict_name, dict_name);
  }
}

void fesenko::union_cmd(data_t &data, std::istream &in)
{
  std::string line = "";
  std::getline(in, line);
  std::string new_dict_name = get_cmd_word(line);
  std::string dict_name1 = get_cmd_word(line);
  std::string dict_name2 = get_cmd_word(line);
  make_union(data, new_dict_name, dict_name1, dict_name2);
  while (!line.empty()) {
    std::string dict_name = get_cmd_word(line);
    make_union(data, new_dict_name, new_dict_name, dict_name);
  }
}

void fesenko::rename_cmd(data_t &data, std::istream &in)
{
  std::string line = "";
  std::getline(in, line);
  std::string dict_name = get_cmd_word(line);
  std::string new_dict_name = get_cmd_word(line);
  if (!line.empty()) {
    throw std::invalid_argument("Wrong input");
  }
  if (dict_name.compare(new_dict_name) == 0) {
    return;
  }
  hash_t temp = data.at(dict_name).data;
  data.erase(dict_name);
  data.insert(std::make_pair(new_dict_name, temp));
}

void fesenko::insert_cmd(data_t &data, std::istream &in)
{
  std::string line = "";
  std::getline(in, line);
  std::string dict_name = get_cmd_word(line);
  std::string word = get_cmd_word(line);
  if (line.empty()) {
    throw std::invalid_argument("Wrong input");
  }
  hash_t &dict = data.at(dict_name).data;
  while (!line.empty()) {
    size_t number = stoull(get_cmd_word(line));
    insert_in_asc_order(dict[word].data, number);
  }
}

std::ostream &fesenko::print_word_cmd(const data_t &data, std::istream &in, std::ostream &out)
{
  std::string line = "";
  std::getline(in, line);
  std::string dict_name = get_cmd_word(line);
  std::string word = get_cmd_word(line);
  if (!line.empty()) {
    throw std::invalid_argument("Wrong input");
  }
  const hash_t &hash = data.at(dict_name).data;
  print_word(hash.at(word).data, word, out);
  return out;
}

std::ostream &fesenko::print_dict_cmd(const data_t &data, std::istream &in, std::ostream &out)
{
  std::string line = "";
  std::getline(in, line);
  std::string dict_name = get_cmd_word(line);
  if (!line.empty()) {
    throw std::invalid_argument("Wrong input");
  }
  const hash_t &hash = data.at(dict_name).data;
  for (auto &it: hash) {
    if (!it.word.empty()) {
      print_word(it.data, it.word, out);
      if (!it.collision_list.empty()) {
        for (auto &it2: it.collision_list) {
          print_word(it2.second, it2.first, out);
        }
      }
    }
  }
  return out;
}

std::ostream &fesenko::find_cmd(const data_t &data, std::istream &in, std::ostream &out)
{
  std::string line = "";
  std::getline(in, line);
  std::string dict_name = get_cmd_word(line);
  std::string word = get_cmd_word(line);
  if (!line.empty()) {
    throw std::invalid_argument("Wrong input");
  }
  const hash_t &hash = data.at(dict_name).data;
  if (!hash.find(word)) {
    out << "Not found\n";
  } else {
    print_word(hash.at(word).data, word, out);
  }
  return out;
}

#ifndef SUBCOMMANDS_H
#define SUBCOMMANDS_H
#include <iostream>
#include <dictionary/forward-list/forwardList.h>
#include "hashTable.h"
namespace fesenko
{
  using list_t = ForwardList< size_t >;
  using hash_t = HashTable< list_t >;
  using data_t = HashTable< hash_t >;
  void read_file_cmd(data_t &data, std::istream &in);
  void delete_dict_cmd(data_t &data, std::istream &in);
  void delete_word_cmd(data_t &data, std::istream &in);
  void complement_cmd(data_t &data, std::istream &in);
  void intersect_cmd(data_t &data, std::istream &in);
  void union_cmd(data_t &data, std::istream &in);
  void rename_cmd(data_t &data, std::istream &in);
  void insert_cmd(data_t &data, std::istream &in);

  std::ostream &print_word_cmd(const data_t &data, std::istream &in, std::ostream &out);
  std::ostream &print_dict_cmd(const data_t &data, std::istream &in, std::ostream &out);
  std::ostream &find_cmd(const data_t &data, std::istream &in, std::ostream &out);
}
#endif

#ifndef SUBFUNCTIONS_H
#define SUBFUNCTIONS_H
#include <ostream>
#include <dictionary/forward-list/forwardList.h>
#include "hashTable.h"
namespace fesenko
{
  using list_t = ForwardList< size_t >;
  using hash_t = HashTable< list_t >;
  using data_t = HashTable< hash_t >;
  std::string get_cmd_word(std::string &line);
  ForwardList< std::string > parse_text_line(const std::string line);
  void print_word(const list_t &list, const std::string word, std::ostream &out);
  void insert_in_asc_order(list_t &list, size_t number);
  void make_complementation(data_t &data, std::string new_dict_name, std::string dict_name1, std::string dict_name2);
  void make_complementation(list_t &new_list, const list_t &list1, const list_t &list2);
  void make_intersection(data_t &data, std::string new_dict_name, std::string dict_name1, std::string dict_name2);
  void make_intersection(list_t &new_list, const list_t &list1, const list_t &list2);
  void make_union(data_t &data, std::string new_dict_name, std::string dict_name1, std::string dict_name2);
  void make_union(list_t &list1, const list_t &list2);
}
#endif

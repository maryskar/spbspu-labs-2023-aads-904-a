#include "workWithIO.h"

namespace potapova
{
  static const char* parseKey(const char* cur_sym_ptr, long long& key)
  {
    char* end_conv_ptr = nullptr;
    key = std::strtoll(cur_sym_ptr, &end_conv_ptr, 10);
    if (errno == ERANGE || (*end_conv_ptr != ' ' && *end_conv_ptr != '\0'))
    {
      return nullptr;
    }
    return end_conv_ptr;
  }

  static const char* parseValue(const char* cur_sym_ptr, std::string& value)
  {
    while (!(*cur_sym_ptr == ' ' || *cur_sym_ptr == '\0'))
    {
      value.push_back(*cur_sym_ptr);
      ++cur_sym_ptr;
    }
    return cur_sym_ptr;
  }
}

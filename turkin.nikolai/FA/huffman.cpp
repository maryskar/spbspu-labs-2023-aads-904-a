#include "huffman.hpp"
#include "data-types.hpp"
#include "huffman-tree.hpp"

turkin::PType::PType(const phrase_t & phrase):
  phrase_(phrase),
  encoding_(""),
  map_()
{}

const turkin::phrase_t & turkin::PType::get_phrase()
{
  return phrase_;
}

const turkin::encoding_t & turkin::PType::get_encoding()
{
  return encoding_;
}

const turkin::encoding_map_t & turkin::PType::get_char_encoding()
{
  return map_;
}

turkin::encoding_t turkin::details::encode(const phrase_t & phrase, const encoding_map_t & map)
{
  encoding_t result;
  for (char i: phrase)
  {
    result += map.at(i);
  }
  return result;
}

turkin::phrase_t turkin::details::decode(const turkin::encoding_t &, const encoding_map_t &)
{
  return "";
}

turkin::encoding_t turkin::details::recode(const phrase_t & phrase, encoding_map_t & map)
{
  encoding_t result;
  for (auto i: phrase)
  {
    result += map.at(i);
  }
  return result;
}

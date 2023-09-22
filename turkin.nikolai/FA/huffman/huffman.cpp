#include "huffman.hpp"
#include "FA/data-types.hpp"

turkin::PType::PType(const phrase_t & phrase):
  phrase_(phrase),
  encoding_(""),
  map_()
{}

const turkin::phrase_t & turkin::PType::get_phrase() const
{
  return phrase_;
}

const turkin::encoding_t & turkin::PType::get_encoding() const
{
  return encoding_;
}

const turkin::encoding_map_t & turkin::PType::get_char_encoding() const
{
  return map_;
}

std::pair< turkin::encoding_t, turkin::encoding_map_t > turkin::details::encode(const phrase_t & phrase)
{
  encoding_map_t result;
  result.insert(' ', 0);
}

turkin::phrase_t turkin::details::decode(const turkin::encoding_t & encoding, const encoding_map_t & map)
{}

turkin::encoding_t turkin::details::recode(const phrase_t & phrase, encoding_map_t & map)
{
  encoding_t result;
  for (auto i: phrase)
  {
    result += map.at(i);
  }
  return result;
}

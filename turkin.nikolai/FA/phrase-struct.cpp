#include "phrase-struct.hpp"

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

const turkin::encoding_map_t & turkin::PType::get_encoding_map()
{
  return map_;
}

void turkin::PType::set_encoding(const encoding_t & encoding)
{
  encoding_ = encoding;
}

void turkin::PType::set_encoding_map(const encoding_map_t & map)
{
  map_ = map;
}

#include "commands.hpp"

#include <stdexcept>
#include <fstream>

#include "data-types.hpp"
#include "huffman-code.hpp"

namespace
{
  using namespace turkin;

  std::ostream & get_phrase_func(PType & lhs, PType & rhs, std::ostream & out)
  {
    return out << "encoding for phrase: " << lhs.get_phrase() << " | " << encode(lhs.get_phrase(), rhs.get_encoding_map());
  }

  std::ostream & info_phrase_func(PType & lhs, PType & rhs, std::ostream & out)
  {
    out << lhs.get_phrase() << " ";
    out << encode(lhs.get_phrase(), rhs.get_encoding_map()) << "\n";
    out << rhs.get_encoding_map() << "\n";
    out << "a_w: " << lhs.get_encoding().size() << "\n";
    out << "b_w: " << encode(lhs.get_phrase(), rhs.get_encoding_map()).size();
    return out;
  }

  std::ostream & info_state_func(PType & lhs, PType & rhs, std::ostream & out)
  {
    auto lhs_lhs_encoding = encode(lhs.get_phrase(), lhs.get_encoding_map());
    auto lhs_rhs_encoding = encode(lhs.get_phrase(), rhs.get_encoding_map());
    auto rhs_rhs_encoding = encode(rhs.get_phrase(), rhs.get_encoding_map());
    auto rhs_lhs_encoding = encode(rhs.get_phrase(), lhs.get_encoding_map());
    out << lhs.get_phrase() << "\n";
    out << lhs_lhs_encoding << "\n";
    out << lhs_rhs_encoding << "\n";
    out << "difference: " << lhs_lhs_encoding.size() - lhs_rhs_encoding.size() << "\n";
    out << rhs.get_phrase() << "\n";
    out << rhs_rhs_encoding << "\n";
    out << rhs_lhs_encoding << "\n";
    out << "difference: " << rhs_rhs_encoding.size() - rhs_lhs_encoding.size();
    return out;
  }
}

std::ostream & turkin::new_phrase(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out)
{
  phrase_t phrase = "";
  in >> phrase;
  PType p_new(phrase);
  p_dict.insert(phrase, p_new);
  return out << "added phrase: " << phrase;
}

std::ostream & turkin::new_encoding(phrase_dict_t & p_dict, encoding_dict_t & e_dict, std::istream & in, std::ostream & out)
{
  phrase_t phrase = "";
  in >> phrase;
  auto & ptype = p_dict.at(phrase);
  HType e_new(phrase);
  ptype.set_encoding(encode(ptype.get_phrase(), e_new.get_encoding_map()));
  ptype.set_encoding_map(e_new.get_encoding_map());
  e_dict.insert(phrase, e_new);
  return out << "added encoding for phrase: " << ptype.get_phrase() << " | " << ptype.get_encoding();
}

std::ostream & turkin::new_merge(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out)
{
  phrase_t phrase_a = "";
  phrase_t phrase_b = "";
  in >> phrase_a >> phrase_b;
  p_dict.at(phrase_a);
  p_dict.at(phrase_b);
  phrase_t phrase = phrase_a + " " + phrase_b;
  PType p_new(phrase);
  p_dict.insert(phrase, p_new);
  return out << "added phrase: " << phrase;
}

std::ostream & turkin::get_phrase(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out)
{
  phrase_t phrase_a = "";
  phrase_t phrase_b = "";
  in >> phrase_a >> phrase_b;
  auto & lhs = p_dict.at(phrase_a);
  auto & rhs = p_dict.at(phrase_b);
  return get_phrase_func(lhs, rhs, out);
}

std::ostream & turkin::get_encoding(phrase_dict_t &, encoding_dict_t & e_dict, std::istream & in, std::ostream & out)
{
  phrase_t phrase = "";
  in >> phrase;
  return out << e_dict.at(phrase).get_encoding_map();
}

std::ostream & turkin::get_full(phrase_dict_t & p_dict, encoding_dict_t & e_dict, std::istream & in, std::ostream & out)
{
  phrase_t phrase_a = "";
  phrase_t phrase_b = "";
  in >> phrase_a >> phrase_b;
  auto & lhs = p_dict.at(phrase_a);
  auto & rhs = p_dict.at(phrase_b);
  return get_phrase_func(lhs, rhs, out) << e_dict.at(phrase_b).get_encoding_map();
}

std::ostream & turkin::del_phrase(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out)
{
  std::string phrase = "";
  in >> phrase;
  p_dict.erase(phrase);
  return out << "deleted: " << phrase;
}

std::ostream & turkin::del_encoding(phrase_dict_t & p_dict, encoding_dict_t & e_dict, std::istream & in, std::ostream & out)
{
  std::string phrase = "";
  in >> phrase;
  e_dict.erase(phrase);
  p_dict.at(phrase).set_encoding(encoding_t());
  p_dict.at(phrase).set_encoding_map(encoding_map_t());
  return out << "deleted: " << phrase;
}

std::ostream & turkin::re_encoding(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out)
{
  phrase_t phrase_a = "";
  phrase_t phrase_b = "";
  in >> phrase_a >> phrase_b;
  auto & ptype_a = p_dict.at(phrase_a);
  auto & ptype_b = p_dict.at(phrase_b);
  return out << encode(ptype_a.get_phrase(), ptype_b.get_encoding_map());
}

std::ostream & turkin::info_phrase(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out)
{
  phrase_t phrase_a = "";
  phrase_t phrase_b = "";
  in >> phrase_a >> phrase_b;
  auto & lhs = p_dict.at(phrase_a);
  auto & rhs = p_dict.at(phrase_b);
  return info_phrase_func(lhs, rhs, out);
}

std::ostream & turkin::info_state(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out)
{
  phrase_t phrase_a = "";
  phrase_t phrase_b = "";
  in >> phrase_a >> phrase_b;
  auto & lhs = p_dict.at(phrase_a);
  auto & rhs = p_dict.at(phrase_b);
  return info_state_func(lhs, rhs, out);
}

std::ostream & turkin::info_algorithm(phrase_dict_t &, encoding_dict_t &, std::istream &, std::ostream & out)
{
  return out << "https://en.wikipedia.org/wiki/Huffman_coding";
}

std::ostream & turkin::save_phrase(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out)
{
  phrase_t phrase_a = "";
  phrase_t phrase_b = "";
  std::string path = "";
  in >> phrase_a >> phrase_b >> path;
  std::fstream file(path);
  if (!file.is_open())
  {
    throw std::runtime_error("bad file name");
  }
  auto & lhs = p_dict.at(phrase_a);
  auto & rhs = p_dict.at(phrase_b);
  info_phrase_func(lhs, rhs, file);
  return out;
}

std::ostream & turkin::save_full(phrase_dict_t & p_dict, encoding_dict_t &, std::istream & in, std::ostream & out)
{
  phrase_t phrase_a = "";
  phrase_t phrase_b = "";
  std::string path = "";
  in >> phrase_a >> phrase_b >> path;
  std::fstream file(path);
  if (!file.is_open())
  {
    throw std::runtime_error("bad file name");
  }
  for (auto & p: p_dict)
  {
    info_phrase_func(p.second, p.second, file) << "\n\n";
  }
  return out;
}

std::ostream & turkin::help(phrase_dict_t &, encoding_dict_t &, std::istream & in, std::ostream & out)
{
  std::string type = "";
  in >> type;
  if (type == "NEW")
  {
    out << "NEW-PHRASE <phrase> - добавляет новую фразу\n";
    out << "NEW-ENCODING <phrase> - добавляет кодировку для фразы\n";
    out << "NEW-MERGE <lhs> <rhs> - соединяет две существуетвующие фразы в одну через пробел";
  }
  else if (type == "GET")
  {
    out << "GET-PHRASE <lhs> <rhs> - выводит фразу lhs и ее закодированный вид, используя кодировку rhs\n";
    out << "GET-ENCODING <phrase> - выводит коды символов для фразы\n";
    out << "GET-FULL <rhs> <rhs> - выполняет GET PHRASE и GET ENCODING для rhs по фразе lhs";
  }
  else if (type == "DEL")
  {
    out << "DEL-PHRASE <phrase> - удаляет фразу\n";
    out << "DEL-ENCODING <phrase> - удаляет кодировку фразы";
  }
  else if (type == "RE")
  {
    out << "RE-ENCODING <lhs> <rhs> - выводит закодированную фразу lhs, используя кодировку rhs";
  }
  else if (type == "INFO")
  {
    out << "INFO-PHRASE <lhs> <rhs> - выводит фразу lhs, кодировку rhs,";
    out << "частоту символов lhs, коды символов rhs, вес до кодировки и после\n";
    out << "INFO-STATE <lhs> <rhs> - выводит фразы lhs rhs, их кодировки";
    out << "(lhs - lhs, lhs - rhs, rhs - rhs, rhs - lhs) и разницу в весе\n";
    out << "INFO-ALGORITHM - выводит информацию об алгоритме сжатия";
  }
  else if (type == "SAVE")
  {
    out << "SAVE-PHRASE <lhs> <rhs> <file> - сохраняет вывод INFO PHRASE для фразы в файл\n";
    out << "SAVE-FULL <file> - сохраняет вывод INFO PHRASE для всех фраз в файл, используя кодировки lhs - lhs";
  }
  else
  {
    throw std::runtime_error("bad input");
  }
  return out;
}

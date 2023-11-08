#include "customtypes.h"
#include <iomanip>

std::istream& dmitriev::operator>>(std::istream& inp, SeparatorIO&& data)
{
  std::istream::sentry sentry(inp);
  if (!sentry)
  {
    return inp;
  }

  char c = '\0';
  inp >> c;
  if (inp && c != data.expected)
  {
    inp.setstate(std::ios::failbit);
  }

  return inp;
}

std::ostream& dmitriev::operator<<(std::ostream& out, const SeparatorIO& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  return out << data.expected;
}

std::istream& dmitriev::operator>>(std::istream& inp, LableIO&& data)
{
  std::istream::sentry sentry(inp);
  if (!sentry)
  {
    return inp;
  }

  for (size_t i = 0; i < data.expected.length(); i++)
  {
    inp >> SeparatorIO{data.expected[i]};
  }

  return inp;
}

std::ostream& dmitriev::operator<<(std::ostream& out, const LableIO& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  return out << data.expected;
}

std::istream& dmitriev::operator>>(std::istream& inp, DoubleI&& data)
{
  std::istream::sentry sentry(inp);
  if (!sentry)
  {
    return inp;
  }

  return inp >> data.value >> SeparatorIO{'d'};
}

std::ostream& dmitriev::operator<<(std::ostream& out, const DoubleO& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  return out << std::fixed << std::setprecision(1) << data.value << SeparatorIO{'d'};
}

std::istream& dmitriev::operator>>(std::istream& inp, LongLongI&& data)
{
  std::istream::sentry sentry(inp);
  if (!sentry)
  {
    return inp;
  }

  return inp >> data.value >> SeparatorIO{'l'} >> SeparatorIO{'l'};
}

std::ostream& dmitriev::operator<<(std::ostream& out, const LongLongO& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  return out << data.value << SeparatorIO{'l'} << SeparatorIO{'l'};
}

std::istream& dmitriev::operator>>(std::istream& inp, StringI&& data)
{
  std::istream::sentry sentry(inp);
  if (!sentry)
  {
    return inp;
  }

  return std::getline(inp >> SeparatorIO{'"'}, data.value, '"');
}

std::ostream& dmitriev::operator<<(std::ostream& out, const StringO& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  return out << SeparatorIO{'"'} << data.value << SeparatorIO{'"'};
}

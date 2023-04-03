#ifndef CALC_DATA_TYPE_H
#define CALC_DATA_TYPE_H

namespace kryuchkova
{
  struct calc_data_type
  {
    void GetPriority(const char data);
    union
    {
      char data;
      int priority;
    };
    bool isDigit(const char data);
  };
}

#endif

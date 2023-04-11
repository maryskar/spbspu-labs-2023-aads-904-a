#ifndef CALC_DATA_TYPE_H
#define CALC_DATA_TYPE_H

namespace kryuchkova
{
  struct calc_data_type
  {
    union
    {
      char data;
      int priority;
    };
    void GetPriority(const char data);
    bool isDigit(const char data);
  };
}

#endif

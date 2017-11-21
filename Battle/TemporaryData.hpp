#ifndef game_TemporaryData_HPP
#define game_TemporaryData_HPP


#include"gmbb_Standard.hpp"
#include"CharacterData.hpp"


namespace gmbb{
namespace tmp{


class
NameBuffer
{
  char16_t  data[8] = {0};

  uint16_t  length=0;

public:
  const char16_t*  get_data() const noexcept{return data;}

  uint16_t  get_length() const noexcept{return length;}

  void  clear() noexcept
  {
    data[0] = 0;

    length = 0;
  }

  void  push(char16_t  c) noexcept{data[  length++] = c;}
  void   pop(           ) noexcept{data[--length  ] = 0;}

};


extern NameBuffer  name_buffer;

extern CharacterData  character_data;

extern uint32_t  last_time;
extern uint32_t  next_time;


}}




#endif





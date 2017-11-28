#ifndef game_TemporaryData_HPP
#define game_TemporaryData_HPP


#include"gmbb_Standard.hpp"
#include"CharacterData.hpp"


namespace gmbb{
namespace tmp{


extern NameBuffer  name_buffer;

extern CharacterData  character_data;

extern CharacterData  enemy;

extern Action  action;

extern uint32_t  last_time;
extern uint32_t  next_time;


}}




#endif





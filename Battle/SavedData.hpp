#ifndef game_SavedData_HPP
#define game_SavedData_HPP


#include"Player.hpp"
#include"CharacterData.hpp"
#include"Pointer.hpp"


namespace gmbb{
namespace saved_data{


extern CharacterData  characters[4];

struct
Party
{
  static constexpr int  max_number_of_members = 4;

  rw_ptr<CharacterData>  members[max_number_of_members] = {0};

  int  number_of_members = 0;

};


extern Party  party;


}}




#endif





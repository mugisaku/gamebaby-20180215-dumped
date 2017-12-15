#include"Startup.hpp"
#include"SystemData.hpp"
#include"SavedData.hpp"




namespace gmbb{


namespace{


void
return_from_character_making(int  retval) noexcept
{
  terminate_character_making();


  auto&  h = sav::hero_table[0];

  h = tmp::hero;

  h.set_name(tmp::name_buffer.to_string());

  sav::party.members[0] = make_rw(h);

  sav::party.number_of_members = 1;
}


void
initialize() noexcept
{
  coprocesses::push(return_from_character_making,coprocess_of_character_making);
}


}


void
terminate_party_making() noexcept
{
}


const coprocess
coprocess_of_party_making("party making",initialize,nullptr);


}





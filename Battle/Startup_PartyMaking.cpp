#include"Startup.hpp"
#include"SystemData.hpp"
#include"SavedData.hpp"




namespace gmbb{


namespace{


FixedString
label("party making");


coreturn_t
ret_hunger;


void
return_from_character_making(int  retval) noexcept
{
  terminate_character_making();

    if(ret_hunger)
    {
      ret_hunger(retval);
    }


  auto&  h = sav::hero_table[0];

  h = tmp::hero;

  h.set_name(tmp::name_buffer.to_string());

  sav::party.members[0] = &h;

  sav::party.number_of_members = 1;
}


}


void
terminate_party_making() noexcept
{
}


void
start_party_making(coreturn_t  ret) noexcept
{
  ret_hunger = ret;

  start_character_making(return_from_character_making,0);
}


}





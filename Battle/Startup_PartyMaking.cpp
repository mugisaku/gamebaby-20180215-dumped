#include"Startup.hpp"
#include"SystemData.hpp"
#include"SavedData.hpp"




namespace{


void
step(uint32_t&  pc) noexcept
{
    switch(pc)
    {
  case(0):
      gbstd::playworks::push(nullptr,playwork_of_character_making);
      ++pc;
      break;
  case(1):
      terminate_character_making();

        {
          auto&  h = sav::hero_table[0];

          h = tmp::hero;

          h.set_name(tmp::name_buffer.to_string());

          sav::party.members[0] = gbstd::make_rw(h);

          sav::party.number_of_members = 1;
        }


      ++pc;
  default:
      gbstd::playworks::pop();
    }
}


}


void
terminate_party_making() noexcept
{
}


const gbstd::playwork
playwork_of_party_making("party making",step);





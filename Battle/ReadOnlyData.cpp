#include"ReadOnlyData.hpp"
#include"gbdn.hpp"


namespace gmbb{
namespace ro{


namespace{


std::vector<PlayerBase>
player_base_table_entity;


std::vector<BattleCommand>
command_table_entity;


}


const std::vector<PlayerBase>&
player_base_table = player_base_table_entity;


void
load() noexcept
{
  gbdn::list  ls;

    try
    {
      ls.open("../battle.gamn");
    }


    catch(const gbdn::stream_error&  e)
    {
      e.print();

      return;
    }


    for(auto&  v: ls)
    {
        if(v.is_string())
        {
          auto&  s = v.get_string();

          auto  subv = s.get_value();

            if(s.compare(5,"class") && subv && subv->is_list())
            {
                for(auto&  vv: subv->get_list())
                {
                    if(vv.is_string())
                    {
                      auto&  ss = vv.get_string();

                      auto  vvv = ss.get_value();

                        if(vvv && vvv->is_list())
                        {
                          player_base_table_entity.emplace_back(ss.get_data(),vvv->get_list());
                        }
                    }
                }
            }
        }
    }
}


}}





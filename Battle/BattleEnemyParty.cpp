#include"BattleEnemyParty.hpp"
#include"ReadOnlyData.hpp"


namespace gmbb{


void
EnemyParty::
load(const char*  name_, const gbdn::list&  ls)
{
  name = name_;

    for(auto&  v: ls)
    {
        if(v.is_string())
        {
            for(auto&  ene: ro::enemy_table)
            {
              auto&  name = ene.get_name();

              gbdn::string_view  sv(name.data(),name.size());

                if(v.get_string() == sv)
                {
                  enemies.emplace_back(make_ro(ene));
                }
            }
        }
    }
}


}





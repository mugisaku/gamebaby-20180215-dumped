#include"BattleEnemyParty.hpp"
#include"ReadOnlyData.hpp"




void
EnemyParty::
load(std::string_view  name, const gbdn::list&  ls)
{
  m_name = name;

    for(auto&  v: ls)
    {
        if(v.is_string())
        {
            for(auto&  ene: ro::enemy_table)
            {
              auto&  name = ene.get_name();

              std::string_view  sv(name.data(),name.size());

                if(v.get_string() == sv)
                {
                  m_enemies.emplace_back(gbstd::make_ro(ene));
                }
            }
        }
    }
}





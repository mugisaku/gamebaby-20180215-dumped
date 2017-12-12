#include"ReadOnlyData.hpp"
#include"gbdn.hpp"


namespace gmbb{
namespace ro{


namespace{


std::vector<PlayerBase>
player_base_table_entity;


std::vector<BattleCommand>
command_table_entity;


std::vector<Enemy>
enemy_table_entity;


std::vector<EnemyParty>
enemy_party_table_entity;


template<typename  T>
void
read(const gbdn::list&  ls, std::vector<T>&  tbl)
{
    for(auto&  v: ls)
    {
        if(v.is_string())
        {
          auto&  s = v.get_string();

          auto  vv = s.get_value();

            if(vv && vv->is_list())
            {
              tbl.emplace_back(s.get_data(),vv->get_list());
            }
        }
    }
}


}


const std::vector<PlayerBase>&
player_base_table = player_base_table_entity;


const std::vector<Enemy>&
enemy_table = enemy_table_entity;


const std::vector<EnemyParty>&
enemy_party_table = enemy_party_table_entity;


const std::vector<BattleCommand>&
command_table = command_table_entity;


void
load() noexcept
{
  gbdn::list  ls;

    try
    {
      ls.open("../battle.gb.txt");
    }


    catch(const gbdn::stream_error&  e)
    {
      e.print();

      return;
    }


    try
    {
        for(auto&  v: ls)
        {
            if(v.is_string())
            {
              auto&  s = v.get_string();

              auto  subv = s.get_value();

                if((s == gbdn::string_view("class")) && subv && subv->is_list())
                {
                  read(subv->get_list(),player_base_table_entity);
                }

              else
                if((s == gbdn::string_view("enemy")) && subv && subv->is_list())
                {
                  read(subv->get_list(),enemy_table_entity);
                }

              else
                if((s == gbdn::string_view("enemy_party")) && subv && subv->is_list())
                {
                  read(subv->get_list(),enemy_party_table_entity);
                }

              else
                if((s == gbdn::string_view("command")) && subv && subv->is_list())
                {
                  read(subv->get_list(),command_table_entity);
                }
            }
        }
    }


    catch(gbdn::value_was_not_found&  not_f)
    {
      printf("%s is not found.\n",not_f.name);
    }


    for(auto&  ene: enemy_table_entity)
    {
      ene.refresh_command_table();
    }


    for(auto&  plb: player_base_table_entity)
    {
      plb.refresh_command_table();
    }
}


}}





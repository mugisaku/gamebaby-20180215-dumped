#include"ReadOnlyData.hpp"
#include"libgbdn/gbdn.hpp"


namespace ro{


namespace{


std::vector<PlayerBase>
player_base_table_entity;


constexpr size_t  max_number_of_commands = 90;

gbstd::entry_list<BattleCommand,max_number_of_commands>
command_table;


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


template<typename  T, size_t  N>
void
read(const gbdn::list&  ls, gbstd::entry_list<T,N>&  tbl)
{
    for(auto&  v: ls)
    {
        if(v.is_string())
        {
          auto&  s = v.get_string();

          auto  vv = s.get_value();

            if(vv && vv->is_list())
            {
              auto&  e = tbl[s.get_view()];

              e.load(vv->get_list());
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


const BattleCommand&
get_command(gbstd::string_view  name) noexcept
{
  return command_table[name];
}



void
load() noexcept
{
  gbdn::list  ls;

    try
    {
      ls.open("../battle.gb.txt");
    }


    catch(const tok::stream_context&  ctx)
    {
      ctx.print();

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

                if((s == gbstd::string_view("class")) && subv && subv->is_list())
                {
                  read(subv->get_list(),player_base_table_entity);
                }

              else
                if((s == gbstd::string_view("enemy")) && subv && subv->is_list())
                {
                  read(subv->get_list(),enemy_table_entity);
                }

              else
                if((s == gbstd::string_view("enemy_party")) && subv && subv->is_list())
                {
                  read(subv->get_list(),enemy_party_table_entity);
                }

              else
                if((s == gbstd::string_view("command")) && subv && subv->is_list())
                {
                  read(subv->get_list(),command_table);
                }
            }
        }
    }


    catch(gbdn::value_was_not_found&  not_f)
    {
      printf("%s is not found.\n",not_f.name);
    }
}


}





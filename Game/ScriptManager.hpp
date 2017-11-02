#ifndef ScriptManager_HPP
#define ScriptManager_HPP


#include"gmbb_Script.hpp"


namespace gmbb{


script::Value const*  find_message_script(char const*  value_name) noexcept;
script::Value const*  find_routine_script(char const*  value_name) noexcept;
script::Value const*  find_shop_script(char const*  value_name) noexcept;
script::Value const*  find_role_script(char const*  value_name) noexcept;

void  load_script_file(char const*  filepath) noexcept;

}




#endif




